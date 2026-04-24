#pragma once
#include "GameObject.h"
#include "Component.h"
#include <InputModule.h>
#include "Include/Text.h"
#include "functional"
namespace Clicker
{
	class GameMaster : public GameObject
	{
	public:

		float points = 0;
		float clickPower = 1;
		float autoPoints = 0;
		GameMaster();
	};
	class GameMasterInput : public Component 
	{
	public:
		InputModule* input = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class GameMasterText : public Text {
	public:
		std::function<void(GameMasterText* text)> changeText;
		GameMasterText(std::function<void(GameMasterText* text)> changeTextTo, sf::Font font);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		GameMaster* gameMaster = nullptr;
	};
}

