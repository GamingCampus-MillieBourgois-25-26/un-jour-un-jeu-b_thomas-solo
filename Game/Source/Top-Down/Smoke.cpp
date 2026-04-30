#include <SpriteRender.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/Top-Down/Smoke.h>

TopDown::Smoke::Smoke()
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	CreateComponent<SpriteRender>(ressource->GetTexture("smoke"), sf::IntRect({ 0,0 }, { 98,107 }));
	CreateComponent<SmokeMovement>();
	
}


void TopDown::SmokeMovement::Update(TimeModule* timeModule)
{
	owner->Move(speed * timeModule->GetDeltaTime(), speed * timeModule->GetDeltaTime());
	owner->Rotate(rotateSpeed * timeModule->GetDeltaTime());
	lifeTime -= timeModule->GetDeltaTime();
	if (lifeTime <= 0) {
		owner->GetScene()->DestroyObject(owner);
	}
	speed = std::max(speed - 15 * timeModule->GetDeltaTime(), 0.f);
	rotateSpeed = std::max(rotateSpeed - 10 * timeModule->GetDeltaTime(), 0.f);
}
