#include "Include/SceneMenu.h"
#include <Include/Button.h>
#include <Engine.h>
#include <SceneModule.h>
#include <Include/BulletHell/BulletHell.h>
#include <CollisionBox.h>
#include <Include/BasicBox.h>
#include <Include/Text.h>
#include <RessourceModule.h>
#include <Include/TowerDefense/TowerDefense.h>
#include <Include/Clicker/Clicker.h>
#include <Include/Match3/Match3.h>
#include <Include/Top-Down/TopDown.h>

SceneMenu::SceneMenu()
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();


	GameObject* buttonHellBullet = new GameObject();

	buttonHellBullet->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<BulletHell::BulletHell>("BulletHell"));
		});

	buttonHellBullet->CreateComponent<BasicBox>(200,50);

	Text* text = buttonHellBullet->CreateComponent<Text>(*ressource->GetFont("font"));
	text->text.setString("BulletHell");
	text->text.setFillColor(sf::Color::Black);

	CollisionBox* box = buttonHellBullet->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonHellBullet->SetPosition(400, 100);

	GameObject* buttonTowerDefense = new GameObject();

	buttonTowerDefense->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<TowerDefense::TowerDefense>("BulletHell"));
		});

	buttonTowerDefense->CreateComponent<BasicBox>(200,50);

	text = buttonTowerDefense->CreateComponent<Text>(*ressource->GetFont("font"));
	text->text.setString("Tower Defense");
	text->text.setFillColor(sf::Color::Black);

	box = buttonTowerDefense->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonTowerDefense->SetPosition(400, 175);

	GameObject* buttonClicker = new GameObject();

	buttonClicker->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<Clicker::Clicker>("BulletHell"));
		});

	buttonClicker->CreateComponent<BasicBox>(200,50);

	text = buttonClicker->CreateComponent<Text>(*ressource->GetFont("font"));
	text->text.setString("Clicker");
	text->text.setFillColor(sf::Color::Black);

	box = buttonClicker->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 100));

	buttonClicker->SetPosition(400, 250);

	GameObject* buttonMatch3 = new GameObject();

	buttonMatch3->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<Match3::Match3>("BulletHell"));
		});

	buttonMatch3->CreateComponent<BasicBox>(200,50);

	text = buttonMatch3->CreateComponent<Text>(*ressource->GetFont("font"));
	text->text.setString("Match3");
	text->text.setFillColor(sf::Color::Black);

	box = buttonMatch3->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonMatch3->SetPosition(400, 325);

	GameObject* buttonTopDown = new GameObject();

	buttonTopDown->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<TopDown::TopDown>("BulletHell"));
		});

	buttonTopDown->CreateComponent<BasicBox>(200,50);

	text = buttonTopDown->CreateComponent<Text>(*ressource->GetFont("font"));
	text->text.setString("TopDown");
	text->text.setFillColor(sf::Color::Black);

	box = buttonTopDown->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonTopDown->SetPosition(400, 400);

	AddGameObject(buttonHellBullet, 0);
	AddGameObject(buttonTowerDefense, 0);
	AddGameObject(buttonClicker, 0);
	AddGameObject(buttonMatch3, 0);
	AddGameObject(buttonTopDown, 0);
}
