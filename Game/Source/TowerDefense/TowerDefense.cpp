#include <Include/TowerDefense/TowerDefense.h>
#include <Include/TowerDefense/GameMaster.h>
#include <Include/TowerDefense/ButtonWave.h>
#include <Include/TowerDefense/Build.h>

TowerDefense::TowerDefense::TowerDefense()
{
	GameMaster* gameMaster = new GameMaster();
	gameMaster->SetId(1);
	ButtonWave* button = new ButtonWave();
	button->SetId(2);
	button->SetPosition(600, 100);
	RocketLauncher* launcher = new RocketLauncher();
	launcher->SetPosition(400, 400);
	PasLourd* dummy = new PasLourd(500, gameMaster->GetComponent<WaveManager>());
	dummy->SetPosition(350, 350);
	AddGameObject(gameMaster, 0);
	AddGameObject(button, 0);
	AddGameObject(launcher, 0);
	AddGameObject(dummy, 0);
}
