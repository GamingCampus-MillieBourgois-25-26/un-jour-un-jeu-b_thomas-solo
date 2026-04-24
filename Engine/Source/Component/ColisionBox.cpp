#include "pch.h"
#include "Include/Component/CollisionBox.h"
#include "Include/Engine.h"





void CollisionBox::Init(sf::Vector2f size)
{
	sizeRect = size;
}

void CollisionBox::Start()
{
	rect.size = { owner->GetScale().x * sizeRect.x, owner->GetScale().y * sizeRect.y };
	rect.position = { owner->GetPosition().x - rect.size.x / 2, owner->GetPosition().y - rect.size.y / 2 };
	collisionModule = Engine::GetInstance()->GetModuleManager()->GetModule<CollisionModule>();
}

void CollisionBox::Update(TimeModule* timeModule) {
	rect.position = { owner->GetPosition().x - rect.size.x / 2, owner->GetPosition().y - rect.size.y / 2 };
	rect.size = { owner->GetScale().x * sizeRect.x, owner->GetScale().y * sizeRect.y };
	std::cout << owner->GetName() << ", ";
	collisionModule->colisionBoxs.push_back(this);
	
}

void CollisionBox::Render(WindowModule* windowModule)
{
	/*sf::RectangleShape rectangle(rect.size);
	rectangle.setPosition(rect.position);
	windowModule->GetWindow()->draw(rectangle);*/
}

void CollisionBox::Destroy()
{
	auto it = std::find(collisionModule->colisionBoxs.begin(), collisionModule->colisionBoxs.end(), this);
	if (it != collisionModule->colisionBoxs.end()) {
		collisionModule->colisionBoxs.erase(it);
	}
}

bool CollisionBox::IsColliding(CollisionBox* other) {
	/*Utilise la methode AABB pour trouver les colisions avec une autre colisionBox
	input:
		Une autre boite de colision
	output:
		renvoie True si les 2 boite se touche
		sinon False
	*/
	if (rect.findIntersection(other->rect)) {
		return true;
	}
	return false;
}