#include <Include/Top-Down/ProjectileTopDown.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <Engine.h>

TopDown::Projectile::Projectile()
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	CreateComponent<ProjectileMouvement>();
	SpriteRender* sprite = CreateComponent<SpriteRender>(ressource->GetTexture("TopDownBullet"), sf::IntRect({ 0,0 }, { 12,26 }));
	sprite->offsetRotation = 90;
}

void TopDown::ProjectileMouvement::Start()
{
	bulletSpeed = static_cast<Projectile*>(owner)->bulletSpeed;
}

void TopDown::ProjectileMouvement::Update(TimeModule* timeModule)
{
	float rad = owner->GetRotation() * 3.141 / 180;
	sf::Vector2f direction(cos(rad), sin(rad));
	owner->Move(direction * bulletSpeed * timeModule->GetDeltaTime());
}
