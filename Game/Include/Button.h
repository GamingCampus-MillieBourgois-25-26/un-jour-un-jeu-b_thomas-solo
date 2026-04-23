#pragma once
#include "Component.h"
#include <functional>
#include <InputModule.h>
class Button : public Component
{
public:
	Button(std::function<void()> action);
	std::function<void()> clickAction;
	InputModule* input = nullptr;
	void OnClick();
	void Start()override;
	void Update(TimeModule* timeModule)override;
};

