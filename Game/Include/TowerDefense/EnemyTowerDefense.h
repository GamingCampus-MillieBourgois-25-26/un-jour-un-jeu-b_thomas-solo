#pragma once
#include "GameObject.h"
#include "Component.h"
namespace TowerDefense
{
	class GameMaster;
	class Enemy : public GameObject
	{
	public:
		GameMaster* gameMaster;
		float health;
		float speed;
		float activationTime;
		Enemy(float hp, float spd, float activationTime, GameMaster* _gameMaster, sf::Texture* tex);
	};

	class Mouvement : public Component
	{
	public:
		Enemy* enemy = nullptr;
		std::vector<sf::Vector2f>targets = std::vector<sf::Vector2f>({ sf::Vector2f(200,400), sf::Vector2f(200,100), sf::Vector2f(400,100),sf::Vector2f(400,600),sf::Vector2f(900,600) });
		int currentTarget = 0;
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Destroy()override;
		void Move(sf::Vector2f target, TimeModule* timeModule);

	};
	
}

