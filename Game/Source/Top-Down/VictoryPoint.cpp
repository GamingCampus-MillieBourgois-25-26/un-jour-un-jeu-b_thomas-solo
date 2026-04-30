#include <Include/Top-Down/VictoryPoint.h>
#include <Include/BasicBox.h>

TopDown::VictoryPoint::VictoryPoint()
{
	CreateComponent<BasicBox>(20,20);
	VictoryCollisionBox* box = CreateComponent<VictoryCollisionBox>();
	box->Init({ 20,20 });
}

void TopDown::VictoryCollisionBox::Collide(CollisionBox* other)
{
	if (other->owner->GetId() == 1) {
		std::cout << "Win" << std::endl;
		BasicBox* box = owner->GetComponent<BasicBox>();
		if (box) {
			box->rect.setFillColor(sf::Color::Green);
		}
	}
}
