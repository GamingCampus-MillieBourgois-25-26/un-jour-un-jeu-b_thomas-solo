#include <Include/Clicker/AutoUpgrade.h>
#include <Include/Button.h>
#include <Include/BasicBox.h>
#include <CollisionBox.h>

Clicker::AutoUpgrade::AutoUpgrade(float cst, float _nbAuto, GameMaster* _gameMaster):cost(cst), nbAuto(_nbAuto), gameMaster(_gameMaster)
{
	CreateComponent<Button>([this]()
		{
			if(gameMaster->points >= cost)
			{
				gameMaster->points -= cost;
				cost *= 1.5;
				nbUpgrade++;
				nbAutoTotal = nbUpgrade * nbAuto * upgrade;
				gameMaster->autoPoints += nbAuto * upgrade;
			}
		});

	CreateComponent<BasicBox>(50, 50);
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init({ 50,50 });
}
