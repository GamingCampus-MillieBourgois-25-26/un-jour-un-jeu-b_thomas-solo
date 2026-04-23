#include "Include/SceneMenu.h"
#include <Include/Button.h>
#include <Engine.h>
#include <SceneModule.h>
#include <Include/BulletHell/BulletHell.h>
#include <CollisionBox.h>
#include <Include/BasicBox.h>

SceneMenu::SceneMenu()
{
	GameObject* buttonHellBullet = new GameObject();
	buttonHellBullet->CreateComponent<Button>([]() {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->AddScene<BulletHell::BulletHell>("BulletHell"));
		});
	buttonHellBullet->CreateComponent<BasicBox>(200,100);
	CollisionBox* box = buttonHellBullet->CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(200, 100));

	buttonHellBullet->SetPosition(400, 400);
	AddGameObject(buttonHellBullet, 0);
}
