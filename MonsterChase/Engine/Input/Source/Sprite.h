#ifndef SPRITE_H
#define SPRITE_H

#include "Vector3D.h"
#include "GLib.h"

namespace Engine
{
	struct BoundingBox
	{
		Vector3D center;
		Vector3D extent;

		BoundingBox(Vector3D cent, Vector3D ext) :
			center(cent),
			extent(ext)
		{
		}
	};

	class Sprite
	{
	public:
		Sprite();
		~Sprite();
		void SetImage(GLib::Sprites::Sprite * sprite);
		GLib::Sprites::Sprite * GetImage();
		void SetBoundingBoxExtent(Vector3D bounds);
		void SetBoundingBoxCenter(Vector3D cent);
		BoundingBox GetBoundingBox();
		void SetRotation(float degree);
		float GetRotation();
		void SetVelocity(Vector3D velo);
		Vector3D GetVelocity();
		void SetSize(Vector3D pos);
		Vector3D GetSize();
	private:
		Vector3D size;
		GLib::Sprites::Sprite * image;
		BoundingBox spriteBox;
		float rotation;
		Vector3D velocity;
	};
}

#endif // !SPRITE_H
