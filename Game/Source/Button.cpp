#include <Include/Button.h>
#include <Engine.h>
#include <CollisionBox.h>

Button::Button(std::function<void()> action)
{
	clickAction = action;
}

void Button::OnClick()
{
	clickAction();
}

void Button::Start()
{
	input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
}

void Button::Update(TimeModule* timeModule)
{
	CollisionBox* box = owner->GetComponent<CollisionBox>();
	if (box != nullptr) {
		if (input->GetMouseButtonPressing(sf::Mouse::Button::Left) && box->rect.contains(input->GetMousePosition())) {
			OnClick();
		}
	}
	else {
		std::cout << "no box found";
	}
}
