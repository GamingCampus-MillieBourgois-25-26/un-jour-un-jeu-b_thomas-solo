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
		PaternManager* paternManager;
		virtual void Start() {};
		virtual int Update(TimeModule* timeModule) {};
		virtual void End() {};
	};
	class PaternManager : public Component
	{
	public:
		std::vector<Patern> paterns;
		int currentPatern = 0;
		void Update(TimeModule* timeModule)override;
	};
	class DumbShoot : public Patern 
	{
	public:
		RessourceModule* ressourceModule = nullptr;
		float shootTimer = 3;
		float shootTimerMax = 3;
		void Shoot();
		void Start()override;
		int Update(TimeModule* timeModule)override;
	};
}
