#include "pch.h"
#include "CircleCollision.h"

CircleCollision::CircleCollision(float rds):radius(rds)
{
}

bool CircleCollision::IsColliding(CollisionBox* other)
{
    CircleCollision* circle = dynamic_cast<CircleCollision*>(other);
    if (circle == nullptr) {
        
        if (CalculateDistance(other->rect.position) < radius) {
            return true;
        }
        if (CalculateDistance({ other->rect.position.x + other->rect.size.x, other->rect.position.y }) < radius) {
            return true;
        }
        if (CalculateDistance({ other->rect.position.x, other->rect.position.y + other->rect.size.y }) < radius) {
            return true;
        }
        if (CalculateDistance(other->rect.position + other->rect.size) < radius) {
            return true;
        }
    }
    else
    {
        std::cout << "par-la" << std::endl;
        if (CalculateDistance(circle->owner->GetPosition()) < radius + circle->radius) {
            return true;
        }
    }
    return false;
}

void CircleCollision::Collide(CollisionBox* other)
{
    collide(other);
}

float CircleCollision::CalculateDistance(sf::Vector2f point)
{
    sf::Vector2f direction = point - owner->GetPosition();
    float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
    return distance;
}
