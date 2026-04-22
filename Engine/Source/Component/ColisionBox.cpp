#include "pch.h"
#include "Include/Component/ColisionBox.h"
#include "Include/Engine.h"





void ColisionBox::Init(sf::Vector2f size)
{
	sizeRect = size;
}

void ColisionBox::Start()
{
	rect.size = { owner->GetScale().x * sizeRect.x, owner->GetScale().y * sizeRect.y };
	rect.position = { owner->GetPosition().x - rect.size.x / 2, owner->GetPosition().y - rect.size.y / 2 };
	colisionModule = Engine::GetInstance()->GetModuleManager()->GetModule<ColisionModule>();
}

void ColisionBox::Update(TimeModule* timeModule) {
	rect.position = { owner->GetPosition().x - rect.size.x / 2, owner->GetPosition().y - rect.size.y / 2 };
	rect.size = { owner->GetScale().x * sizeRect.x, owner->GetScale().y * sizeRect.y };

	colisionModule->colisionBoxs.push_back(this);
	
}

void ColisionBox::Render(WindowModule* windowModule)
{
	sf::RectangleShape rectangle(rect.size);
	rectangle.setPosition(rect.position);
	windowModule->GetWindow()->draw(rectangle);
}

void ColisionBox::Destroy()
{
	auto it = std::find(colisionModule->colisionBoxs.begin(), colisionModule->colisionBoxs.end(), this);
	if (it != colisionModule->colisionBoxs.end()) {
		colisionModule->colisionBoxs.erase(it);
	}
}

bool ColisionBox::IsColliding(ColisionBox other) {
	/*Utilise la methode AABB pour trouver les colisions avec une autre colisionBox
	input:
		Une autre boite de colision
	output:
		renvoie True si les 2 boite se touche
		sinon False
	*/
	if (rect.findIntersection(other.rect)) {
		return true;
	}
	return false;
}