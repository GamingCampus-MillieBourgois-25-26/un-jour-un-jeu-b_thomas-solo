#include <Engine.h>
#include <Include/Text.h>
#include <RessourceModule.h>
#include <Include/Button.h>
#include <Include/BasicBox.h>
#include <CollisionBox.h>
#include <Include/SceneVictoire.h>
#include <Include/LastSceneBackground.h>

SceneVictoire::SceneVictoire()
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	GameObject* victoryText = new GameObject();
	Text* text = victoryText->CreateComponent<Text>(*ressourceModule->GetFont("font"));
	text->text.setString("Victoire !");
	text->text.setCharacterSize(32);
	victoryText->SetPosition(400, 300);

	GameObject* buttonMenu = new GameObject();

	buttonMenu->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->GetScene("SceneMenu"));
		});

	buttonMenu->CreateComponent<BasicBox>(200.f, 50.f);

	text = buttonMenu->CreateComponent<Text>(*ressourceModule->GetFont("font"));
	text->text.setString("Menu");
	text->text.setFillColor(sf::Color::Black);

	CollisionBox* box = buttonMenu->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonMenu->SetPosition(600, 600);

	GameObject* buttonRestart = new GameObject();

	buttonRestart->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene(sceneModule->GetLastScene()));
		});

	buttonRestart->CreateComponent<BasicBox>(200.f, 50.f);

	text = buttonRestart->CreateComponent<Text>(*ressourceModule->GetFont("font"));
	text->text.setString("Restart");
	text->text.setFillColor(sf::Color::Black);

	box = buttonRestart->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 50));

	buttonRestart->SetPosition(200, 600);

	GameObject* background = new GameObject();
	background->CreateComponent<LastSceneBackground>();

	AddGameObject(background, 0);
	AddGameObject(victoryText, 1);
	AddGameObject(buttonMenu, 1);
	AddGameObject(buttonRestart, 1);
}

SceneVictoire* SceneVictoire::Reset()
{
	return new SceneVictoire();
}

