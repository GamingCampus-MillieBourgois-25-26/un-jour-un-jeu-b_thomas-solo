#pragma once
#include "Scene.h"
namespace BulletHell
{
	class BulletHell : public Scene
	{
	public:
		BulletHell();
		BulletHell* Reset()override;
	};

}
