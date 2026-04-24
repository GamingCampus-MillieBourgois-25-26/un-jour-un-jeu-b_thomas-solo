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
	CreateComponent<CooldownUpdater>();
	CircleCollision* circle = GetComponent<CircleCollision>();
	circle->collide = [this](CollisionBox* other) {
		
		if (other->owner->GetName() == "Enemy" && shootCooldown <= 0) {
			shootCooldown = shootCooldownMax;
			Enemy* enemy = static_cast<Enemy*>(other->owner);
			RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
			CollisionRocket* box = CreateComponent<CollisionRocket>();
			box->Init({ 20,20 });
			Projectile* projectile = new Projectile(200, ressourceModule->GetTexture("TowerDefenseMissile"),enemy);
			projectile->SetName("Enemy");
			projectile->SetPosition(GetPosition());
			projectile->SetRotation(rand() % 360);
			CircleCollision* circle = projectile->CreateComponent<CircleCollision>(20);
			circle->collide = [projectile](CollisionBox* other) {
				if (projectile->explose && other->owner->GetName() == "Enemy") {
					Enemy* enemy = static_cast<Enemy*>(other->owner);
					enemy->health -= 10;
					if (enemy->health <= 0) {
						enemy->waveManger->DestroyEnemy(enemy);
						std::cout << "boum" << std::endl;
					}
				}
				};
			scene->AddGameObject(projectile, 1);
		}
		};
}

TowerDefense::Projectile::Projectile(float spd, sf::Texture* tex, Enemy* emy) :speed(spd), enemy(emy)
{;
	SpriteRender* sprite = CreateComponent<SpriteRender>(tex, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(tex->getSize())));
	CreateComponent<ProjectileMovement>();
}
void TowerDefense::CollisionRocket::Collide(CollisionBox* other)
{
	if (other->owner->GetName() == "Enemy") {
		static_cast<Projectile*>(owner)->explose = true;
	}
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

void TowerDefense::CooldownUpdater::Start()
{
	build = static_cast<Build*>(owner);
}

void TowerDefense::CooldownUpdater::Update(TimeModule* timeModule)
{
	build->shootCooldown -= timeModule->GetDeltaTime();
}
