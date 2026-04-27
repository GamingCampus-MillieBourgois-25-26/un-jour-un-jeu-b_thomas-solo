#include "pch.h"
#include "Include/GameObject.h"
#include "Include/Component.h"
#include <iostream>



GameObject::GameObject(std::string _name, int ID)
{
	name = _name; 
	id = ID;
}

void GameObject::Start() {
	for (Component* component : components)
	{
		component->Start();
	}
}
void GameObject::Update(TimeModule* timeModule) {
	//std::cout << components.size() << ", ";
	for (Component* component : components)
	{
		component->Update(timeModule);
	}
}
void GameObject::Render(WindowModule* windowModule) {
	for(Component* component: components)
	{
		component->Render(windowModule);
	}
}
void GameObject::Destroy() {
	for (Component* component : components)
	{
		component->Destroy();
		delete component;
	}
	components.clear();
}


