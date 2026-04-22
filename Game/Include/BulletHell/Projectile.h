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
		float rotateSpeed;
		float gainRotation;
		Projectile(float speed, float rotateSpeed, float gainRot, sf::Texture* tex);
	};
	class ProjectileMovement : public Component 
	{
	public:
		Projectile* projectile;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};

}
