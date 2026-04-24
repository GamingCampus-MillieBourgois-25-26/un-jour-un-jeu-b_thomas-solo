#include <Include/Clicker/UpgradeAutoUp.h>
#include <Include/Button.h>
#include <Include/BasicBox.h>
#include <CollisionBox.h>

Clicker::UpgradeAutoUp::UpgradeAutoUp(float _cost, float _upgrade, AutoUpgrade* _autoUpgrade, GameMaster* _gameMaster): cost(_cost), upgrade(_upgrade), autoUpgrade(_autoUpgrade), gameMaster(_gameMaster)
{
	
	CreateComponent<Button>([this]()
		{
			if (gameMaster->points >= cost)
			{
				gameMaster->points -= cost;
				cost *= 1.5;
				gameMaster->autoPoints -= autoUpgrade->nbAutoTotal;
				autoUpgrade->upgrade += upgrade;
				autoUpgrade->nbAutoTotal = autoUpgrade->nbAuto * autoUpgrade->upgrade * autoUpgrade->nbUpgrade;
				gameMaster->autoPoints += autoUpgrade->nbAutoTotal;
			}
		});

	CreateComponent<BasicBox>(50, 50);
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init({ 50,50 });
}
