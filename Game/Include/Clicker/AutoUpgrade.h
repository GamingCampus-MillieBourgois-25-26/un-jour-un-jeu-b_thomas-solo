#pragma once
#include "GameObject.h"
#include <Include/Clicker/GameMasterClicker.h>
namespace Clicker
{
	class AutoUpgrade : public GameObject
	{
	public:
		GameMaster* gameMaster = nullptr;
		int cost;
		float upgrade = 1;
		float nbAuto;
		float nbAutoTotal = 0;
		int nbUpgrade = 0;
		AutoUpgrade(float cost, float nbAuto, GameMaster* _gameMaster);

	};
}

