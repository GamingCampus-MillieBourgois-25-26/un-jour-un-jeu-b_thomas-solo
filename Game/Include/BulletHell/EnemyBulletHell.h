#pragma once
#include "GameObject.h"
#include "Component.h"
class RessourceModule;
namespace BulletHell
{
	class Enemy : public GameObject
	{
	public:
		Enemy(RessourceModule* ressourceModule);
	};
	class PaternManager;
	class Patern
	{
	public:
		PaternManager* paternManager = nullptr;
		virtual void Start(PaternManager* paternManag) { paternManager = paternManag; };
		virtual int Update(TimeModule* timeModule) { return 1; };
		virtual void End() {};
	};
	class PaternManager : public Component
	{
	public:
		std::vector<Patern*> paterns;
		int currentPatern = 0;
		template<typename Patern, typename... Param>
		void CreatePatern(Param... parameters);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Destroy()override;
	};
	class DumbShoot : public Patern 
	{
	public:
		RessourceModule* ressourceModule = nullptr;
		float timer = 10;
		float shootTimer = 3;
		float shootTimerMax = 3;
		void Shoot();
		void Start(PaternManager* paternManag)override;
		int Update(TimeModule* timeModule)override;
	};
	class TeleportationPatern : public Patern {
	public:
		float tpTimer = 4;
		int Update(TimeModule* timeModule)override;
	};
	class HellMovement : public Patern {
	public:
		float shootTimer = 0;
		float shootTimerMax;
		float speed;
		sf::Vector2f target;
		RessourceModule* ressourceModule;
		HellMovement(float x, float y, float timer, float spd);
		void Start(PaternManager* paternManag)override;
		int Update(TimeModule* timeModule)override;
		void Move(TimeModule* timeModule);
		void Shoot();
	};
}
#include "EnemyBulletHell.inl"
