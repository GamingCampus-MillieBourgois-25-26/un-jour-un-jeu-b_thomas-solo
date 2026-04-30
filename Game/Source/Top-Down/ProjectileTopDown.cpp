#include <Include/Top-Down/ProjectileTopDown.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <CollisionBox.h>

TopDown::Projectile::Projectile(sf::Texture* tex, GameObject* _owner): owner(_owner)
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	CreateComponent<ProjectileMouvement>();
	SpriteRender* sprite = CreateComponent<SpriteRender>(tex, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(tex->getSize())));
	sprite->offsetRotation = 90;
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init({ 10,10 });
	SetId(3);
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
