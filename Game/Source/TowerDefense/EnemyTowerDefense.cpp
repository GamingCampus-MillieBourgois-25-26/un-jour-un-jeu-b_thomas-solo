#include <Include/TowerDefense/EnemyTowerDefense.h>
#include <SpriteRender.h>
#include <Engine.h>
#include <RessourceModule.h>
#include <CollisionBox.h>
#include "Include/TowerDefense/GameMaster.h"
#include <Include/BasicBox.h>

TowerDefense::Enemy::Enemy(float hp, float spd, float aTime, GameMaster* _gameMaster, sf::Texture* tex): health(hp), speed(spd), activationTime(aTime), gameMaster(_gameMaster){
	CollisionBox* box = CreateComponent<CollisionBox>();
	box->Init({64,64});
	CreateComponent<Mouvement>();
	CreateComponent<BasicBox>(64,64);
	name = "Enemy";
}

void TowerDefense::Mouvement::Start()
{
	enemy = static_cast<Enemy*>(owner);
	//owner->SetPosition(-100, 400);
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
void TowerDefense::Mouvement::Destroy()
{
	//std::cout << "objet detruit";
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