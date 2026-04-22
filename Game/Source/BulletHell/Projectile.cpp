#include <Include/BulletHell/Projectile.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <ColisionBox.h>

BulletHell::Projectile::Projectile(float spd, RessourceModule* ressource):speed(spd)
{
	ColisionBox* box = CreateComponent<ColisionBox>();
	box->Init(sf::Vector2f(54,9));
	SpriteRender* sprite = CreateComponent<SpriteRender>(ressource->GetTexture("BulletHellBullet"), sf::IntRect({ 0,0 }, { 9,54 }));
	sprite->offsetRotation = 90;
	CreateComponent<ProjectileMovement>();
}

void BulletHell::ProjectileMovement::Start()
{
	projectile = static_cast<Projectile*>(owner);
}

void BulletHell::ProjectileMovement::Update(TimeModule* timeModule)
{
	float angle = owner->GetRotation();
	float rad = angle * 3.14159265f / 180.f;
	sf::Vector2f direction(std::cos(rad), std::sin(rad));
	owner->Move(direction.x * projectile->speed, direction.y * projectile->speed);
}
