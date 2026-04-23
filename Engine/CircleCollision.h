#pragma once
#include "Include/Component/CollisionBox.h"
#include <functional>
class CircleCollision : public CollisionBox
{
public:
	float radius;
	std::function<void(CollisionBox* other)> collide;
	CircleCollision(float radius);
	bool IsColliding(CollisionBox* other)override;
	void Collide(CollisionBox* other)override;
	float CalculateDistance(sf::Vector2f point);

};

