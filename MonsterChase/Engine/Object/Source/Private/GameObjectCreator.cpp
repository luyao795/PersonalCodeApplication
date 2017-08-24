#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "lua.hpp"
#include "DebugPrint.h"
#include "GameObject.h"
#include "SmartPointer.h"
#include "PhysicsInfo.h"
#include "ReferenceCounter.h"
#include "MessagingSystem.h"
#include "GameObjectCreator.h"

using namespace std;

namespace Engine
{
	int GetLuaTableEntries(lua_State * i_pState, int i_index)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);
		lua_len(i_pState, i_index);
		assert(lua_type(i_pState, -1) == LUA_TNUMBER);
		lua_Integer table_entries = lua_tointeger(i_pState, -1);
		lua_pop(i_pState, 1);
		assert(table_entries <= INT_MAX);
		return static_cast<int>(table_entries);
	}

	size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);
		size_t	index = 0;
		lua_pushnil(i_pState);
		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				lua_Integer lValue = lua_tointeger(i_pState, -1);
				assert(lValue <= INT_MAX);
				o_pInts[index] = lValue < INT_MAX ? int(lValue) : INT_MAX;
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as int array.\n", index );
			}
			lua_pop(i_pState, 1);
			if (++index == i_numInts)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}
		return index;
	}

	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);
		size_t				index = 0;
		lua_pushnil(i_pState);
		while (lua_next(i_pState, i_index - 1) != 0)
		{
			if (lua_type(i_pState, -1) == LUA_TNUMBER)
			{
				o_pFloats[index] = float(lua_tonumber(i_pState, -1));
			}
			else
			{
				// DEBUG_PRINT( "Expected a number at position %d while reading table as float array.\n", index );
			}
			// pop the value now that we've retrieved it
			lua_pop(i_pState, 1);
			if (++index == i_numFloats)
			{
				lua_pop(i_pState, 1);
				break;
			}
		}
		return index;
	}

	size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats)
	{
		assert(i_pArrayKey);
		lua_pushstring(i_pState, i_pArrayKey);
		i_indexTable--;
		int type = lua_gettable(i_pState, i_indexTable);

		size_t itemsRead = 0;
		if (type == LUA_TTABLE)
			itemsRead = ReadFloatArray(i_pState, i_indexTable, o_pFloats, i_numFloats);
		else
		{
			// DEBUG_PRINT( "Expected Lua table for %s found value of type %d.\n", i_pArrayKey, type );
		}
		lua_pop(i_pState, 1);
		return itemsRead;
	}

	Vector3 GetVector3(lua_State * i_pState, int i_index)
	{
		assert(i_pState);
		assert(lua_gettop(i_pState) >= -i_index);
		assert(lua_type(i_pState, i_index) == LUA_TTABLE);
		const size_t		numFloats = 3;
		float				v[numFloats] = { 0 };
		size_t	readFloats = ReadFloatArray(i_pState, i_index, v, numFloats);
		return Vector3(v[0], v[1], v[2]);
	}

	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile)
	{
		assert(i_pFilename != NULL);

		FILE * pFile = NULL;

		errno_t fopenError = fopen_s(&pFile, i_pFilename, "rb");
		if (fopenError != 0)
			return NULL;

		assert(pFile != NULL);

		int FileIOError = fseek(pFile, 0, SEEK_END);
		assert(FileIOError == 0);

		long FileSize = ftell(pFile);
		assert(FileSize >= 0);

		FileIOError = fseek(pFile, 0, SEEK_SET);
		assert(FileIOError == 0);

		uint8_t * pBuffer = new uint8_t[FileSize];
		assert(pBuffer);

		size_t FileRead = fread(pBuffer, 1, FileSize, pFile);
		assert(FileRead == FileSize);

		fclose(pFile);

		o_sizeFile = FileSize;

		return pBuffer;
	}

	PhysicsInfo * CreatePhysicsInfo(const char * i_pFilename)
	{
		SmartPointer<GameObject> * player = new SmartPointer<GameObject>(new GameObject());
		PhysicsInfo * info = new PhysicsInfo(0.0f, 0.0f);

		info->SetGameObjectSMPTR(player);

		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);
		luaL_openlibs(pLuaState);
		// Read in a file
		size_t		sizeFile = 0;
		// Remember to change the path to find the correct file
		uint8_t *	pFileContents = LoadFile(i_pFilename, sizeFile);

		if (pFileContents  && sizeFile)
		{
			int result = 0;

			// Do the initial buffer parsing
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			assert(result == 0);
			lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);

			int	type = LUA_TNIL;
			// Find the global variable named "Player" and push it onto stack.
			// If it doesn't find it it pushes a nil value instead
			result = lua_getglobal(pLuaState, "Player");
			assert(result == LUA_TTABLE);

			// Get the Actor name from the Player table
			// 1. Push the key string
			lua_pushstring(pLuaState, "name");
			// 2. Get the value associated with the key
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			const char * pName = lua_tostring(pLuaState, -1);
			if (pName == NULL)
				pName = "Player";
			// 3. Remove the value from the stack now that we're done with it
			lua_pop(pLuaState, 1);

			// Get the Actors name from the Player table
			lua_pushstring(pLuaState, "initial_position");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		Position[3] = { 0.0f };
			ReadFloatArray(pLuaState, -1, Position, 3);

			player->GetGameObject()->SetPosition(Position[0], Position[1]);

			// we're done with the "initial_position table - pop it
			lua_pop(pLuaState, 1);

			lua_pushstring(pLuaState, "physics_settings");
			type = lua_gettable(pLuaState, -2);
			// It either needs to be a table or not there (no physics applied)
			assert((type == LUA_TNIL) || (type == LUA_TTABLE));
			if (type == LUA_TTABLE)
			{
				lua_pushstring(pLuaState, "mass");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TNUMBER);
				lua_pushstring(pLuaState, "drag");
				type = lua_gettable(pLuaState, -3);
				assert(type == LUA_TNUMBER);
				float mass = float(lua_tonumber(pLuaState, -2));
				float drag = float(lua_tonumber(pLuaState, -1));

				info->SetMass(mass);
				info->SetDrag(drag);

				// pop the "mass" and "drag" values together
				lua_pop(pLuaState, 2);
			}
			// we're done with the "physics_settings" table - pop it
			// NOTE: If it didn't exist Lua would have pushed a nil value so still need the pop
			lua_pop(pLuaState, 1);

			delete[] pFileContents;

			lua_close(pLuaState);
		}
		return info;
	}

	SmartPointer<GameObject> * CreateGameObject(const char * i_pFilename, PhysicsInfo * info)
	{
		SmartPointer<GameObject> * player = new SmartPointer<GameObject>(new GameObject(), new ReferenceCounter());

		info->SetGameObjectSMPTR(player);

		lua_State * pLuaState = luaL_newstate();
		assert(pLuaState);
		luaL_openlibs(pLuaState);
		// Read in a file
		size_t		sizeFile = 0;
		// Remember to change the path to find the correct file
		uint8_t *	pFileContents = LoadFile(i_pFilename, sizeFile);

		if (pFileContents  && sizeFile)
		{
			int result = 0;

			// Do the initial buffer parsing
			result = luaL_loadbuffer(pLuaState, reinterpret_cast<char *>(pFileContents), sizeFile, nullptr);
			assert(result == 0);
			lua_pcall(pLuaState, 0, 0, 0);
			assert(result == 0);

			int	type = LUA_TNIL;
			// Find the global variable named "Player" and push it onto stack.
			// If it doesn't find it it pushes a nil value instead
			result = lua_getglobal(pLuaState, "Player");
			assert(result == LUA_TTABLE);

			// Get the Actor name from the Player table
			// 1. Push the key string
			lua_pushstring(pLuaState, "name");
			// 2. Get the value associated with the key
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TSTRING);
			const char * pName = lua_tostring(pLuaState, -1);
			if (pName == NULL)
				pName = "Player";
			// 3. Remove the value from the stack now that we're done with it
			lua_pop(pLuaState, 1);

			// Get the Actors name from the Player table
			lua_pushstring(pLuaState, "initial_position");
			type = lua_gettable(pLuaState, -2);
			assert(type == LUA_TTABLE);

			float		Position[3] = { 0.0f };
			ReadFloatArray(pLuaState, -1, Position, 3);

			player->GetGameObject()->SetPosition(Position[0], Position[1]);

			// we're done with the "initial_position" table - pop it
			lua_pop(pLuaState, 1);

			lua_pushstring(pLuaState, "physics_settings");
			type = lua_gettable(pLuaState, -2);
			// It either needs to be a table or not there (no physics applied)
			assert((type == LUA_TNIL) || (type == LUA_TTABLE));
			if (type == LUA_TTABLE)
			{
				lua_pushstring(pLuaState, "mass");
				type = lua_gettable(pLuaState, -2);
				assert(type == LUA_TNUMBER);
				lua_pushstring(pLuaState, "drag");
				type = lua_gettable(pLuaState, -3);
				assert(type == LUA_TNUMBER);
				float mass = float(lua_tonumber(pLuaState, -2));
				float drag = float(lua_tonumber(pLuaState, -1));

				info->SetMass(mass);
				info->SetDrag(drag);

				// pop the "mass" and "drag" values together
				lua_pop(pLuaState, 2);
			}
			// we're done with the "physics_settings" table - pop it
			// NOTE: If it didn't exist Lua would have pushed a nil value so still need the pop
			lua_pop(pLuaState, 1);

			delete[] pFileContents;

			lua_close(pLuaState);
		}
		return player;
	}
}