#include <Include/TowerDefense/ButtonWave.h>
#include <Include/Button.h>
#include <Engine.h>
#include <Include/BasicBox.h>
#include <CollisionBox.h>
#include <Include/TowerDefense/GameMaster.h>

TowerDefense::ButtonWave::ButtonWave()
{
	CreateComponent<Button>([]() {
		Scene* scene = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->GetMainScene();
		ButtonWave* button = static_cast<ButtonWave*>(scene->GetGameObject(2));
		if(button->active == true)
		{
			GameMaster* master = static_cast<GameMaster*>(scene->GetGameObject(1));
			button->active = false;
			master->nextWave = true;
		}
		});
	CreateComponent<BasicBox>(50.f,50.f);
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(50, 50));
}
