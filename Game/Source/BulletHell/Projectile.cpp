#include <Include/BulletHell/Projectile.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <CollisionBox.h>

BulletHell::Projectile::Projectile(float spd, float rotateSpd, float gainRot, sf::Texture* tex):speed(spd), rotateSpeed(rotateSpd), gainRotation(gainRot)
{
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init(static_cast<sf::Vector2f>(tex->getSize()));
	SpriteRender* sprite = CreateComponent<SpriteRender>(tex, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(tex->getSize())));
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
	float rad = angle * 3.141 / 180.f;
	sf::Vector2f direction(std::cos(rad), std::sin(rad));
	owner->Move(direction.x * projectile->speed * timeModule->GetDeltaTime(), direction.y * projectile->speed * timeModule->GetDeltaTime());
	if (projectile->GetPosition().y > 900) {
		projectile->GetScene()->DestroyObject(projectile);
	}
	projectile->Rotate(projectile->rotateSpeed * timeModule->GetDeltaTime());
	projectile->rotateSpeed += projectile->gainRotation * timeModule->GetDeltaTime();
}
