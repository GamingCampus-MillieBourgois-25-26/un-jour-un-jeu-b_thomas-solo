#pragma once
#include "GameObject.h"
#include "Component.h"
#include "EnemyTowerDefense.h"
#include "Scene.h"
namespace TowerDefense
{
	class GameMaster : public GameObject
	{
	public:
		int currentWave = 0;
		bool nextWave = false;
		GameMaster();

	};
	class GameMasterInput : public Component
	{
	public:
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class Wave 
	{
	public:
		int TotalEnemy;
		int nbPasLourd;
		int nbLourd;
		int nbTropLourd;
		Wave(int nbPasLourd, int nbLourd, int nbTropLourd);
	};
	class WaveManager : public Component 
	{
	public:
		GameMaster* gameMaster = nullptr;
		std::vector<Enemy*> enemies;
		std::vector<Wave> waves;
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void CreateWave(Wave wave);
		template<typename Enemy>
		Enemy* CreateEnemy(int i);
	};
	template<typename Enemy>
	inline Enemy* WaveManager::CreateEnemy(int i)
	{
		Enemy* enemy = new Enemy(i, this);
		owner->GetScene()->AddGameObject(enemy, 1);
		return enemy;
	}
}
