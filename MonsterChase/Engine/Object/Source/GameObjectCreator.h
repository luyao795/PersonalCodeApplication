#ifndef GAMEOBJECTCREATOR_H
#define GAMEOBJECTCREATOR_H

#include "lua.hpp"

using namespace std;

namespace Engine
{
	struct Vector3
	{
		float		m_x, m_y, m_z;
		Vector3(float i_x, float i_y, float i_z) :
			m_x(i_x), m_y(i_y), m_z(i_z)
		{ }
	};

	int GetLuaTableEntries(lua_State * i_pState, int i_index);

	size_t ReadIntArray(lua_State * i_pState, int i_index, int * o_pInts, size_t i_numInts);
	size_t ReadFloatArray(lua_State * i_pState, int i_index, float * o_pFloats, size_t i_numFloats);

	size_t GetFloatArray(lua_State * i_pState, int i_indexTable, const char * i_pArrayKey, float * o_pFloats, size_t i_numFloats);

	Vector3 GetVector3(lua_State * i_pState, int i_index);

	uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);

	PhysicsInfo * CreatePhysicsInfo(const char * i_pFilename);

	SmartPointer<GameObject> * CreateGameObject(const char * i_pFilename, PhysicsInfo * info);
}

#endif // !GAMEOBJECTCREATOR_H