#pragma once
#include"SFML/Graphics.hpp"
#include "GameObject.h"
#include "Include/Module/TimeModule.h"
#include "Include/Module/WindowModule.h"


class GameObject;
class Component
{
	/*Donne une carecteristique logique au GameObject
	faite herite à une classe pour pouvoir faire des choses override les methodes virtuels*/
public:
	GameObject* owner = nullptr;
	void SetOwner(GameObject* _owner);
	virtual void Start() {};
	virtual void Update(TimeModule* timeModule) {};
	virtual void Render(WindowModule* windowModule) {};
	virtual void Destroy() {};
};

