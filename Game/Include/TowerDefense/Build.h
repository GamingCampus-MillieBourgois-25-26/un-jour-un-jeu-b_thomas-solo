#pragma once
#include "GameObject.h"
#include "GameMaster.h"
#include <CollisionBox.h>
namespace TowerDefense
{
	class Build : public GameObject
	{
	public:
		int cost;
		float range;
		float shootCooldown = 0;
		float shootCooldownMax;
		Build(float _range, float shootCooldownMax, float cost);
	};
	class RocketLauncher : public Build {
	public:
		RocketLauncher();

	};
	class CooldownUpdater : public Component
	{
	public:
		Build* build = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};

	

	class Projectile : public GameObject 
	{
	public:
		float speed;
		Enemy* enemy;
		bool explose = false;
		Projectile(float spd, sf::Texture* tex, Enemy* enemy);
	};
	class CollisionRocket : public CollisionBox
	{
	public:
		void Collide(CollisionBox* other)override;
	};

	class ProjectileMovement : public Component
	{
	public:
		Projectile* projectile;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
}

