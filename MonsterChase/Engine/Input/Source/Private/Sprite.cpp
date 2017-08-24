#include "GLib.h"
#include "Vector3D.h"
#include "Sprite.h"

using namespace std;

namespace Engine
{
	Sprite::Sprite() :
		image(NULL),
		spriteBox(BoundingBox(Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f))),
		rotation(0.0f),
		velocity(Vector3D(0.0f, 0.0f, 0.0f))
	{
	}

	Sprite::~Sprite()
	{
		if(image)
			GLib::Sprites::Release(image);
	}

	void Engine::Sprite::SetImage(GLib::Sprites::Sprite * sprite)
	{
		image = sprite;
	}

	GLib::Sprites::Sprite * Sprite::GetImage()
	{
		return image;
	}

	void Engine::Sprite::SetBoundingBoxExtent(Vector3D bounds)
	{
		spriteBox.extent = bounds;
	}

	void Sprite::SetBoundingBoxCenter(Vector3D cent)
	{
		spriteBox.center = cent;
	}

	BoundingBox Sprite::GetBoundingBox()
	{
		return spriteBox;
	}

	void Sprite::SetRotation(float degree)
	{
		rotation = degree;
	}

	float Sprite::GetRotation()
	{
		return rotation;
	}

	void Sprite::SetVelocity(Vector3D velo)
	{
		velocity = velo;
	}

	Vector3D Sprite::GetVelocity()
	{
		return velocity;
	}

	void Sprite::SetSize(Vector3D pos)
	{
		size = pos;
	}

	Vector3D Sprite::GetSize()
	{
		return size;
	}
}