#include <Include/BulletHell/Projectile.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <CollisionBox.h>

BulletHell::Projectile::Projectile(float spd, float rotateSpd, float gainRot, sf::Texture* tex):speed(spd), rotateSpeed(rotateSpd), gainRotation(gainRot)
{
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(9,54));
	SpriteRender* sprite = CreateComponent<SpriteRender>(tex, sf::IntRect({ 0,0 }, { 9,54 }));
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
	owner->Move(direction.x * projectile->speed * timeModule->GetDeltaTime(), direction.y * projectile->speed * timeModule->GetDeltaTime());
	if (projectile->GetPosition().y > 900) {
		projectile->GetScene()->DestroyObject(projectile);
	}
	projectile->Rotate(projectile->rotateSpeed * timeModule->GetDeltaTime());
	projectile->rotateSpeed += projectile->gainRotation * timeModule->GetDeltaTime();
}
