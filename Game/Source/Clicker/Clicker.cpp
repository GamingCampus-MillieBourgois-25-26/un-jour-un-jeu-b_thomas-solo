#include <Include/Clicker/Clicker.h>
#include "GameObject.h"
#include <Include/Button.h>
#include <Include/Clicker/GameMasterClicker.h>
#include <Include/BasicBox.h>
#include <CollisionBox.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/Clicker/AutoUpgrade.h>
#include <Include/Clicker/UpgradeAutoUp.h>
Clicker::Clicker::Clicker()
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	GameMaster* gameMaster = new GameMaster();
	GameObject* buttonClick = new GameObject();
	buttonClick->SetPosition(400, 400);
	buttonClick->CreateComponent<Button>([buttonClick]() 
		{
			GameMaster* gameMaster = static_cast<GameMaster*>(buttonClick->GetScene()->GetGameObject("GameMaster"));
			gameMaster->points += gameMaster->clickPower;
		});

	buttonClick->CreateComponent<BasicBox>(50.f,50.f);
	CollisionBox* box = buttonClick->CreateComponent<CollisionBox>();
	box->Init({ 50,50 });

	AutoUpgrade* buttonAuto = new AutoUpgrade(10.f,10.f, gameMaster);
	buttonAuto->SetPosition(200.f, 500.f);
	
	UpgradeAutoUp* bouttonUpAuto = new UpgradeAutoUp(10.f, 0.5f, buttonAuto, gameMaster);
	bouttonUpAuto->SetPosition(600.f, 200.f);

	GameObject* textPoints = new GameObject();
	textPoints->SetPosition(400.f, 300.f);
	textPoints->CreateComponent<GameMasterText>([](GameMasterText* text)
		{
		text->text.setString(std::to_string(static_cast<int>(text->gameMaster->points)));
		}, *ressourceModule->GetFont("font"));
	GameObject* textAuto = new GameObject();
	textAuto->SetPosition(400.f, 250.f);
	textAuto->CreateComponent<GameMasterText>([](GameMasterText* text) {
		text->text.setString(std::to_string(static_cast<int>(text->gameMaster->autoPoints)));
		}, *ressourceModule->GetFont("font"));

	GameObject* buttonClickPower = new GameObject();
	buttonClickPower->SetPosition(400.f, 100.f);
	buttonClickPower->CreateComponent<Button>([buttonClickPower]()
		{
			GameMaster* gameMaster = static_cast<GameMaster*>(buttonClickPower->GetScene()->GetGameObject("GameMaster"));
			if(gameMaster->points >= gameMaster->clickPower * 10)
			{
				gameMaster->points -= gameMaster->clickPower * 10;
				gameMaster->clickPower += gameMaster->clickPower;
			}
		});
	buttonClickPower->CreateComponent<BasicBox>(50.f, 50.f);
	CollisionBox* boxPower = buttonClickPower->CreateComponent<CollisionBox>();
	boxPower->Init({ 50.f,50.f });
	AddGameObject(buttonClick, 0);
	AddGameObject(gameMaster, 0);
	AddGameObject(textPoints, 0);
	AddGameObject(buttonAuto, 0);
	AddGameObject(bouttonUpAuto, 0);
	AddGameObject(textAuto, 0);
	AddGameObject(buttonClickPower, 0);

}

Clicker::Clicker* Clicker::Clicker::Reset()
{
	return new Clicker();
}
