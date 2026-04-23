#include <SpriteRender.h>
#include <RessourceModule.h>
#include <CollisionBox.h>
#include <Include/BulletHell/Projectile.h>
#include <Engine.h>
#include <Include/BulletHell/EnemyBulletHell.h>
BulletHell::Enemy::Enemy(RessourceModule* ressourceModule)
{
	PaternManager* paternManager = CreateComponent<PaternManager>();
	paternManager->CreatePatern<HellMovement>(600,100,0.2,25);
	paternManager->CreatePatern<TeleportationPatern>();
	paternManager->CreatePatern<DumbShoot>();
	paternManager->CreatePatern<HellMovement>(150,300,0.15,30);
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init(sf::Vector2f(98, 75));
	SpriteRender* sprite = CreateComponent<SpriteRender>(ressourceModule->GetTexture("BulletHellEnemy"), sf::IntRect({ 0,0 }, { 98, 75 }));
	sprite->offsetRotation = 90;
	
}



void BulletHell::PaternManager::Start()
{
	paterns[0]->Start(this);
}

void BulletHell::PaternManager::Update(TimeModule* timeModule)
{
	if (currentPatern < paterns.size())
	{
		if (paterns[currentPatern]->Update(timeModule) == 1) {
			paterns[currentPatern]->End();
			currentPatern += 1;
			if (currentPatern < paterns.size())
				paterns[currentPatern]->Start(this);
		}
	}
}

void BulletHell::PaternManager::Destroy()
{
	for (Patern* patern : paterns) {
		delete patern;
	}
}

void BulletHell::DumbShoot::Shoot()
{
	
	Projectile* projectile = new Projectile(200, 0, 0,ressourceModule->GetTexture("BulletHellBullet"));
	projectile->SetName("Enemy");
	projectile->SetPosition(paternManager->owner->GetPosition());
	projectile->SetRotation(90);
	paternManager->owner->GetScene()->AddGameObject(projectile, 0);

	projectile = new Projectile(200, 0, 0, ressourceModule->GetTexture("BulletHellBullet"));
	projectile->SetName("Enemy");
	projectile->SetPosition(paternManager->owner->GetPosition().x + 15 , paternManager->owner->GetPosition().y);
	projectile->SetRotation(90);
	paternManager->owner->GetScene()->AddGameObject(projectile, 0);

	projectile = new Projectile(200, 0, 0, ressourceModule->GetTexture("BulletHellBullet"));
	projectile->SetName("Enemy");
	projectile->SetPosition(paternManager->owner->GetPosition().x - 15 , paternManager->owner->GetPosition().y);
	projectile->SetRotation(90);
	paternManager->owner->GetScene()->AddGameObject(projectile,0);
}

void BulletHell::DumbShoot::Start(PaternManager* paternManag)
{
	Patern::Start(paternManag);
	ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
}



int BulletHell::DumbShoot::Update(TimeModule* timeModule)
{
	shootTimer -= timeModule->GetDeltaTime();
	timer -= timeModule->GetDeltaTime();
	std::cout << timer << std::endl;
	if (shootTimer < 0) {
		shootTimer = shootTimerMax;
		Shoot();
	}
	if (timer < 0) {
		return 1;
	}
	return 0;
}

int BulletHell::TeleportationPatern::Update(TimeModule* timeModule)
{
	tpTimer -= timeModule->GetDeltaTime();
	if (tpTimer < 0) {
		paternManager->owner->SetPosition(rand() % 600 + 100, rand() % 100 + 100);
		return 1;
	}
	return 0;
}

BulletHell::HellMovement::HellMovement(float x, float y, float timer , float spd): shootTimerMax(timer), speed(spd)
{
	target.x = x;
	target.y = y;

}

void BulletHell::HellMovement::Start(PaternManager* paternManag)
{
	Patern::Start(paternManag);
	ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
}

int BulletHell::HellMovement::Update(TimeModule* timeModule)
{
	if (paternManager->owner->GetPosition() == target) {
		return 1;
	}
	Move(timeModule);
	shootTimer -= timeModule->GetDeltaTime();
	if (shootTimer < 0) {
		shootTimer = shootTimerMax;
		Shoot();
	}
	return 0;
}

void BulletHell::HellMovement::Move(TimeModule* timeModule)
{
	sf::Vector2f direction = target - paternManager->owner->GetPosition();
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= distance;
	if (distance <= speed) {
		paternManager->owner->SetPosition(target);
	}
	else
		paternManager->owner->Move(direction.x * speed * timeModule->GetDeltaTime(), direction.y * speed * timeModule->GetDeltaTime());
}
void BulletHell::HellMovement::Shoot() {
	Projectile* projectile = new Projectile(200, 70, -5, ressourceModule->GetTexture("BulletHellRBullet"));
	projectile->SetName("Enemy");
	projectile->SetPosition(paternManager->owner->GetPosition());
	projectile->SetRotation(rand()%360);
	paternManager->owner->GetScene()->AddGameObject(projectile, 0);
}

