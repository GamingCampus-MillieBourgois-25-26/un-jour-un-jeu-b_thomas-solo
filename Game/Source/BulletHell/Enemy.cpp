#include <Include/BulletHell/Enemy.h>
#include <SpriteRender.h>
#include <RessourceModule.h>
#include <ColisionBox.h>
#include <Include/BulletHell/Projectile.h>
#include <Engine.h>
BulletHell::Enemy::Enemy(RessourceModule* ressourceModule)
{
	PaternManager* patrenManager = CreateComponent<PaternManager>();
	ColisionBox* box = CreateComponent<ColisionBox>();
	box->Init(sf::Vector2f(98, 75));
	SpriteRender* sprite = CreateComponent<SpriteRender>(ressourceModule->GetTexture("BulletHellEnemy"), sf::IntRect({ 0,0 }, { 98, 75 }));
	sprite->offsetRotation = 90;
	
}



void BulletHell::PaternManager::Update(TimeModule* timeModule)
{
	if (paterns[currentPatern].Update(timeModule) == 1) {
		paterns[currentPatern].End();
		currentPatern += 1;
		paterns[currentPatern].Start();
	}
}

void BulletHell::DumbShoot::Shoot()
{
	
	Projectile* projectile = new Projectile(50,ressourceModule);
	projectile->SetName("Enemy");
	paternManager->owner->GetScene()->AddGameObject(projectile,0);
}

void BulletHell::DumbShoot::Start()
{
	ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
}

int BulletHell::DumbShoot::Update(TimeModule* timeModule)
{
	shootTimer -= timeModule->GetDeltaTime();
	if (shootTimer < 0) {
		shootTimer = shootTimerMax;
		Shoot();
	}
	return 0;
}
