#pragma once
#include "GameObject.h"
#include "GameMaster.h"
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
	class Projectile : public GameObject 
	{
	public:
		float speed;
		Enemy* enemy;
		Projectile(float spd, sf::Texture* tex, Enemy* enemy);
	};
	class ProjectileMovement : public Component
	{
	public:
		Projectile* projectile;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
}

