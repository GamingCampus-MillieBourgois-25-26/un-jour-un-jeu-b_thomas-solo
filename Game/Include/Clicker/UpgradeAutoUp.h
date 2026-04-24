#pragma once
#include "GameObject.h"
#include <Include/Clicker/GameMasterClicker.h>
#include "AutoUpgrade.h"
namespace Clicker
{
	class UpgradeAutoUp : public GameObject
	{
	public:
		GameMaster* gameMaster = nullptr;
		AutoUpgrade* autoUpgrade = nullptr;
		float cost;
		float upgrade;
		UpgradeAutoUp(float _cost, float _upgrade, AutoUpgrade* _autoUpgrade, GameMaster* _gameMaster);
	};

}
