#include <Include/TowerDefense/TowerDefense.h>
#include <Include/TowerDefense/GameMaster.h>
#include <Include/TowerDefense/ButtonWave.h>

TowerDefense::TowerDefense::TowerDefense()
{
	GameMaster* gameMaster = new GameMaster();
	gameMaster->SetId(1);
	ButtonWave* button = new ButtonWave();
	button->SetId(2);
	button->SetPosition(600, 100);
	AddGameObject(gameMaster, 0);
	AddGameObject(button, 0);
}
