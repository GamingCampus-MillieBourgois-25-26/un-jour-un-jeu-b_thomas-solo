#include <Include/TowerDefense/GameMaster.h>
#include <iostream>
#include <Include/TowerDefense/ButtonWave.h>

TowerDefense::GameMaster::GameMaster()
{
	WaveManager* wave = CreateComponent<WaveManager>();
	wave->waves.push_back(Wave(50, 10, 3));
	wave->waves.push_back(Wave(50, 20, 6));
	CreateComponent<GameMasterInput>();
}
void TowerDefense::GameMasterInput::Start()
{
}

void TowerDefense::GameMasterInput::Update(TimeModule* timeModule)
{
}

void TowerDefense::WaveManager::Start()
{
	gameMaster = static_cast<GameMaster*>(owner);
}

void TowerDefense::WaveManager::Update(TimeModule* timeModule)
{
	if (gameMaster->currentWave < waves.size())
	{
		ButtonWave* button = static_cast<ButtonWave*>(owner->GetScene()->GetGameObject(2));
		if (gameMaster->nextWave) {
			gameMaster->nextWave = false;
			CreateWave(waves[gameMaster->currentWave]);
			gameMaster->currentWave += 1;
		}
		
	}
	if (enemies.empty()) {
		ButtonWave* button = static_cast<ButtonWave*>(owner->GetScene()->GetGameObject(2));
		button->active = true;
	}
}

void TowerDefense::WaveManager::CreateWave(Wave wave)
{
	int number;
	int activationTime = 0;
	printf("total : %d, %d, %d, %d \n", wave.TotalEnemy, wave.nbPasLourd, wave.nbLourd, wave.nbTropLourd);
	while(wave.TotalEnemy > 0) {
		number = rand() % wave.TotalEnemy;
		if (number < wave.nbPasLourd) {
			wave.nbPasLourd--;
			wave.TotalEnemy--;
			PasLourd* enemy = CreateEnemy<PasLourd>(activationTime);
			enemies.push_back(enemy);

		}
		else if (number < wave.nbPasLourd + wave.nbLourd) {
			wave.nbLourd--;
			wave.TotalEnemy--;
			Lourd* enemy = CreateEnemy<Lourd>(activationTime);
			enemies.push_back(enemy);
		}
		else {
			wave.nbTropLourd--;
			wave.TotalEnemy--;
			TropLourd* enemy = CreateEnemy<TropLourd>(activationTime);
			enemies.push_back(enemy);
		}
		printf("total : %d, %d, %d, %d \n", wave.TotalEnemy, wave.nbPasLourd, wave.nbLourd, wave.nbTropLourd);
		activationTime++;
	}
}

void TowerDefense::WaveManager::DestroyEnemy(Enemy* dEnemy)
{
	for (Enemy* enemy : enemies) {
		auto it = std::find(enemies.begin(), enemies.end(), dEnemy);
		if (it != enemies.end())
		{
			enemies.erase(it);
		}
	}
	dEnemy->GetScene()->DestroyObject(dEnemy);
}

TowerDefense::Wave::Wave(int pasLourd, int lourd, int tropLourd): nbPasLourd(pasLourd), nbLourd(lourd), nbTropLourd(tropLourd)
{
	TotalEnemy = pasLourd + lourd + tropLourd;
}
