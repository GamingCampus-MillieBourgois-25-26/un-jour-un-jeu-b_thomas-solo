#pragma once
#include "GameObject.h"
#include "MapMatch3.h"
namespace Match3
{
	class Candy : public GameObject
	{
	public:
		bool checked = false;
		bool falling = false;
		MapMatch3* map = nullptr;
		float speed = 500;
		void Awake()override;
		Candy(int i);
		void MoveCandy(float posX, float posY);
		void MoveCandy(sf::Vector2f pos);
	};
	class CandyMovement : public Component {
	public:
		sf::Vector2f target;
		Candy* candy = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
}

