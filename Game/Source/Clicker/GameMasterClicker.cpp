#include <Include/Clicker/GameMasterClicker.h>
#include <Engine.h>
#include <functional>
Clicker::GameMaster::GameMaster() {
	name = "GameMaster";
	CreateComponent<GameMasterInput>();
}
void Clicker::GameMasterInput::Start() {
	input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
}
void Clicker::GameMasterInput::Update(TimeModule* timeModule) {
	GameMaster* gameMaster = static_cast<GameMaster*>(owner);
	gameMaster->points += gameMaster->autoPoints * timeModule->GetDeltaTime();

}

Clicker::GameMasterText::GameMasterText(std::function<void(GameMasterText* text)> changeTextTo, sf::Font font): Text(font), changeText(changeTextTo)
{

}

void Clicker::GameMasterText::Start()
{
	Text::Start();
	gameMaster = static_cast<GameMaster*>(owner->GetScene()->GetGameObject("GameMaster"));
}

void Clicker::GameMasterText::Update(TimeModule* timeModule)
{
	Text::Update(timeModule);
	changeText(this);
}

