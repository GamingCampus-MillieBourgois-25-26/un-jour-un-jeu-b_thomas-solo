#pragma once
#include "GameObject.h"
#include "Component.h"
#include <SpriteRender.h>
#include <InputModule.h>
#include "Include/Top-Down/TopDown.h"
#include <RessourceModule.h>
#include "CollisionBox.h"
namespace TopDown
{
	class Player : public Tank
	{
	public:
		Player(RessourceModule* ressourceModule);
	};
	
	class PlayerInput : public Component {
	public:
		InputModule* input = nullptr;
		Player* player = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;

		void MoveForward(float speed);
		void RotateBarrel(float speedRotation);
		void Shoot();
	};
	class CollisionBoxPlayer : public CollisionBox {
	public:
		void Collide(CollisionBox* other)override;
	};
	class Camera : public Component
	{
	private:
		bool isUseing = false;
	public:
		sf::View view;
		sf::Vector2f clampX;
		sf::Vector2f clampY;
		Camera(sf::FloatRect rect, sf::Vector2f _clampX, sf::Vector2f _clampY);
		void Update(TimeModule* timeModule)override;
		void Render(WindowModule* windowModule)override;
		void UseView();
	};

	class ReloadHud : public Component
	{
	public:
		Player* player = nullptr;
		sf::RectangleShape rectBg;
		sf::RectangleShape rectReload;
		sf::Vector2f pos;
		ReloadHud(sf::Vector2f _pos);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Render(WindowModule* windowModule)override;
	};

}

