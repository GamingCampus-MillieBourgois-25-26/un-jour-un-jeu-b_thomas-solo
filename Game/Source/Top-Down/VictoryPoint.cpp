#include <Include/Top-Down/VictoryPoint.h>
#include <Include/BasicBox.h>
#include <Engine.h>

TopDown::VictoryPoint::VictoryPoint()
{
	CreateComponent<BasicBox>(250.f, 50.f);
	VictoryCollisionBox* box = CreateComponent<VictoryCollisionBox>();
	box->Init({ 250.f,50.f });
}

void TopDown::VictoryCollisionBox::Collide(CollisionBox* other)
{
	if (other->owner->GetId() == 1) {
		SceneModule* sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
		sceneModule->SetMain(sceneModule->GetScene("sceneVictoire"));
		BasicBox* box = owner->GetComponent<BasicBox>();
		if (box) {
			box->rect.setFillColor(sf::Color::Green);
		}
	}
}
