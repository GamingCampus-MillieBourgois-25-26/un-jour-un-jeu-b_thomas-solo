#pragma once
#include "GameObject.h"
#include "Component.h"
namespace TowerDefense
{
	class WaveManager;
	class Enemy : public GameObject
	{
	public:
		WaveManager* waveManger;
		float health;
		float speed;
		float activationTime;
		Enemy(float hp, float spd, float activationTime, WaveManager* waveManger);
	};
	class PasLourd : public Enemy
	{
	public:
		PasLourd(float activationTime, WaveManager* _waveManger);
	};
	class Lourd : public Enemy
	{
	public:
		Lourd(float activationTime, WaveManager* _waveManger);
	};
	class TropLourd : public Enemy
	{
	public:
		TropLourd(float activationTime, WaveManager* _waveManger);
	};

	class Mouvement : public Component
	{
	public:
		Enemy* enemy = nullptr;
		std::vector<sf::Vector2f>targets = std::vector<sf::Vector2f>({ sf::Vector2f(200,400), sf::Vector2f(200,100), sf::Vector2f(400,100),sf::Vector2f(400,600),sf::Vector2f(900,600) });
		int currentTarget = 0;
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Move(sf::Vector2f target, TimeModule* timeModule);

	};
	
}

