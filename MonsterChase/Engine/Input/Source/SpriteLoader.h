#ifndef SPRITELOADER_H
#define SPRITELOADER_H

#include "Sprite.h"

namespace Engine
{
	class SpriteLoader
	{
	public:
		SpriteLoader();
		uint8_t * LoadFile(const char * i_pFilename, size_t & o_sizeFile);
		GLib::Sprites::Sprite * CreateSprite(const char * i_pFilename);
		unsigned int GetWidth();
		unsigned int GetHeight();
		unsigned int GetDepth();
	private:
		Sprite * sprite;
		unsigned int curWidth;
		unsigned int curHeight;
		unsigned int curDepth;
	};
}

#endif // !SPRITELOADER_H
