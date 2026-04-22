#pragma once
#include "GameObject.h"
#include "Component.h"
class RessourceModule;
namespace BulletHell
{
	class Projectile : public GameObject
	{
	public:
		float speed = 50;
		Projectile(float speed, RessourceModule* ressource);
	};
	class ProjectileMovement : public Component 
	{
	public:
		Projectile* projectile;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};

}
