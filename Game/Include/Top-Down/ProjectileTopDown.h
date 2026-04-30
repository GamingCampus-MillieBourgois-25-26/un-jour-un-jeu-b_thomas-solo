#pragma once
#include "GameObject.h"
#include "Component.h"
namespace TopDown
{
	class Projectile : public GameObject
	{
	public:
		float bulletSpeed = 300;
		GameObject* owner = nullptr;
		Projectile(sf::Texture* tex, GameObject* _owner);
	};
	class ProjectileMouvement : public Component {
	public:
		float bulletSpeed;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
}

