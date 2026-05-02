#pragma once
#include "GameObject.h"
#include "Component.h"
#include <InputModule.h>
namespace Match3
{
	class Candy;
	class MapMatch3 : public GameObject
	{
	public:
		std::vector<Candy*>map;
		int mapWidth = 10;
		int mapHeight = 10;
		int mapTileSize = 50;
		bool nextFrame = true;
		MapMatch3();
		void InitMap();
		void Awake()override;
		Candy* CreateCandy(int x, int y);
		Candy* MakeCandy(int i, sf::Color color, int x, int y);
		bool IsCandyFalling();
		void PrintMap();
	};
	class MapUpdater : public Component {
	public:
		MapMatch3* map = nullptr;
		InputModule* input = nullptr;
		sf::Vector2i first = sf::Vector2i(-1,-1);
		sf::Vector2i second = sf::Vector2i(-1, -1);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void HandleInput();
		void FillMap();
		bool Gravity();
		void Swap(sf::Vector2i pos1, sf::Vector2i pos2);
		void Swap(int pos1, int pos2);
		void MatchAll();
		sf::Vector2i CheckCandy(int i, int id, std::vector<Candy*> &candyDelete);
		void DeleteCandy(std::vector<Candy*>deleteCandy);
		void PrintCandyDelete(std::vector<Candy*> candies);

	};
	class MapRender : public Component {
	public:
		MapMatch3* map = nullptr;
		sf::RectangleShape border;
		void Start()override;
		void Render(WindowModule* window)override;
	};
}

