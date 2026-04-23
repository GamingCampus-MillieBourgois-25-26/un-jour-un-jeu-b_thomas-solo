#include <Include/TowerDefense/EnemyTowerDefense.h>
#include <SpriteRender.h>
#include <Engine.h>
#include <RessourceModule.h>
#include <CollisionBox.h>
TowerDefense::Enemy::Enemy(float hp, float spd, float aTime): health(hp), speed(spd), activationTime(aTime){
	CreateComponent<CollisionBox>();
	CreateComponent<Mouvement>();
}

TowerDefense::PasLourd::PasLourd(float activationTime): Enemy(10,40,activationTime)
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	SpriteRender* render = CreateComponent<SpriteRender>(ressourceModule->GetTexture("TowerDefensePasLourd"), sf::IntRect({0,0},{64,64}));
}

TowerDefense::Lourd::Lourd(float activationTime): Enemy(25, 20, activationTime)
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	SpriteRender* render = CreateComponent<SpriteRender>(ressourceModule->GetTexture("TowerDefenseLourd"), sf::IntRect({ 0,0 }, { 64,64 }));
}

TowerDefense::TropLourd::TropLourd(float activationTime): Enemy(80, 10, activationTime)
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	SpriteRender* render = CreateComponent<SpriteRender>(ressourceModule->GetTexture("TowerDefenseTropLourd"), sf::IntRect({ 0,0 }, { 64,64 }));
}

void TowerDefense::Mouvement::Start()
{
	enemy = static_cast<Enemy*>(owner);
	owner->SetPosition(-100, 400);
	owner->SetRotation(0);
}

void TowerDefense::Mouvement::Update(TimeModule* timeModule)
{
	if (enemy->activationTime < 0)
	{
		if (currentTarget < targets.size()) {
			Move(targets[currentTarget], timeModule);
			if (owner->GetPosition() == targets[currentTarget]) {
				currentTarget++;
			}
		}
		else {
			std::cout << "lose" << std::endl;
		}
	}
	else
		enemy->activationTime -= timeModule->GetDeltaTime();
}
void TowerDefense::Mouvement::Move(sf::Vector2f target, TimeModule* timeModule) {
	sf::Vector2f direction = target - owner->GetPosition();
	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction /= distance;
	float rad = atan2(direction.y, direction.x);
	float degree = rad * 180 / (float)3.141;
	owner->SetRotation(degree);
	if (distance <= enemy->speed) {
		owner->SetPosition(target);
	}
	else
		owner->Move(direction.x * enemy->speed * timeModule->GetDeltaTime(), direction.y * enemy->speed * timeModule->GetDeltaTime());
}