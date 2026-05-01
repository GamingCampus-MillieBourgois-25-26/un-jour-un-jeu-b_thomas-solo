#include "Include/Top-Down/Obstacle.h"
#include <SpriteRender.h>
#include <Include/Top-Down/TopDown.h>



TopDown::Obstacle::Obstacle(sf::Texture* tex)
{
	CreateComponent<SpriteRender>(tex, sf::IntRect({},static_cast<sf::Vector2i>(tex->getSize())));
	CollisionObstacle* box = CreateComponent<CollisionObstacle>();
	box->Init(static_cast<sf::Vector2f>(tex->getSize()));
	name = "obstacle";
}

void TopDown::CollisionObstacle::Collide(CollisionBox* other)
{
	if (other->owner->GetId() == 1 || other->owner->GetId() == 2) {
		Tank* tank = static_cast<Tank*>(other->owner);
		sf::Vector2f delta = other->owner->GetPosition() - owner->GetPosition();
		if (abs(delta.y) >= abs(delta.x))
		{
			if (delta.y < 0) 
				other->owner->SetPosition(other->owner->GetPosition().x, rect.position.y - other->rect.size.y / 2);
			else 
				other->owner->SetPosition(other->owner->GetPosition().x, rect.position.y + rect.size.y + other->rect.size.y / 2);
		}
		else
		{
			if (delta.x < 0)
				other->owner->SetPosition(rect.position.x - other->rect.size.x / 2, other->owner->GetPosition().y);
			else
				other->owner->SetPosition(rect.position.x + rect.size.x + other->rect.size.x / 2, other->owner->GetPosition().y);
		}
	}
	if (other->owner->GetId() == 3) {
		other->owner->GetScene()->DestroyObject(other->owner);
	}
}
