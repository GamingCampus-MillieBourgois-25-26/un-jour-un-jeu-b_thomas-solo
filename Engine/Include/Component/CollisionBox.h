#pragma once
#include <SFML/Graphics.hpp>
#include "Include/Component.h"
#include "Include/Module/CollisionModule.h"

class CollisionModule;
class CollisionBox : public Component
{
	/*Component de bases dans le moteur
	cette classe permet de creer une boite de colision
	faite la herite sur une autre classe pour donner une action particulier à l'objet parent*/
private:
	CollisionModule* collisionModule = nullptr;
public:
	sf::FloatRect rect;
	sf::Vector2f sizeRect;
	void Init(sf::Vector2f size);
	void Start() override;
	void Update(TimeModule* timeModule) override;
	void Render(WindowModule* windowModule)override;
	void Destroy()override;
	virtual bool IsColliding(CollisionBox* other);
	virtual void Collide(CollisionBox* other) {};
};



