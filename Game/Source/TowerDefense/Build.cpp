#include <Include/TowerDefense/Build.h>
#include <CircleCollision.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <Engine.h>

TowerDefense::Build::Build(float _range, float shootCooldownM, float cst):range(_range), shootCooldownMax(shootCooldownM),cost(cst)
{
	CreateComponent<CircleCollision>(range);
}

TowerDefense::RocketLauncher::RocketLauncher(): Build(50,5,500.f)
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	CreateComponent<SpriteRender>(ressourceModule->GetTexture("TowerDefenseMissileLuncher"), sf::IntRect({ 0, 0 }, { 64,64 }));
	CircleCollision* circle = GetComponent<CircleCollision>();
	circle->collide = [this](CollisionBox* other) {
		Enemy* enemy = static_cast<Enemy*>(other->owner);
		if (enemy && shootCooldown <= 0) {
			shootCooldown = shootCooldownMax;
			RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
			Projectile* projectile = new Projectile(200, ressourceModule->GetTexture("TowerDefenseMissile"),enemy);
			projectile->SetName("Enemy");
			projectile->SetPosition(GetPosition());
			projectile->SetRotation(rand() % 360);
			scene->AddGameObject(projectile, 1);
		}
		else {
			shootCooldown -= Engine::GetInstance()->GetModuleManager()->GetModule<TimeModule>()->GetDeltaTime();
		}
		};
}

TowerDefense::Projectile::Projectile(float spd, sf::Texture* tex, Enemy* emy) :speed(spd), enemy(emy)
{
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init(static_cast<sf::Vector2f>(tex->getSize()));
	SpriteRender* sprite = CreateComponent<SpriteRender>(tex, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(tex->getSize())));
	CreateComponent<ProjectileMovement>();
}

void TowerDefense::ProjectileMovement::Start()
{
	projectile = static_cast<Projectile*>(owner);
}

void TowerDefense::ProjectileMovement::Update(TimeModule* timeModule)
{
	sf::Vector2f direction = projectile->enemy->GetPosition() - projectile->GetPosition();
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance != 0)
		direction /= distance;
	else
		direction = { 1,0 };
	float rad = atan2(direction.y, direction.x);
	projectile->SetRotation(rad * 180 / (float)3.141);
	owner->Move(direction.x * projectile->speed * timeModule->GetDeltaTime(), direction.y * projectile->speed * timeModule->GetDeltaTime());
	if (projectile->GetPosition().y > 900) {
		projectile->GetScene()->DestroyObject(projectile);
	}
}

