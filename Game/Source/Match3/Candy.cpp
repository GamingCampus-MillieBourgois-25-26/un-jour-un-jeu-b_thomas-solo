#include <Include/Match3/Candy.h>
#include "Scene.h"


void Match3::Candy::Awake()
{
	map = static_cast<MapMatch3*>(GetScene()->GetGameObject("Map"));
}

Match3::Candy::Candy(int i): GameObject(i)
{
	CreateComponent<CandyMovement>();
}

void Match3::Candy::MoveCandy(float posX, float posY)
{
	GetComponent<CandyMovement>()->target = sf::Vector2f(posX,posY);
}

void Match3::Candy::MoveCandy(sf::Vector2f pos)
{
	GetComponent<CandyMovement>()->target = pos;
}

void Match3::CandyMovement::Start()
{
	candy = static_cast<Candy*>(owner);
}

void Match3::CandyMovement::Update(TimeModule* timeModule)
{
	sf::Vector2f delta = target - owner->GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance != 0)
	{
		sf::Vector2f direction = delta / distance;

		if (distance <= candy->speed * timeModule->GetDeltaTime())
		{
			owner->SetPosition(target);
			candy->map->nextFrame = true;
		}
		else
		{
			owner->Move(direction * candy->speed * timeModule->GetDeltaTime());
			candy->map->nextFrame = false;
		}
	}
}

void Match3::CandyMovement::Render(WindowModule* window)
{
	if (candy->GetPosition() == target) {
		candy->map->nextFrame = true;
	}
}
