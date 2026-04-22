#pragma once
#include <string>
#include<vector>
#include "SFML/System/Vector2.hpp"
class Scene;
class Component;
class TimeModule;
class WindowModule;
class Transform {
public:
	float position_x = 0;
	float position_y = 0;

	float scale_x = 1;
	float scale_y = 1;

	float rotation = 0;

};
class GameObject
{
	/*Les GameObjects contiennent des components pour la logique
	le gameObjects contient un transform pour la position la rotation et la taille
	on ajoute les component avec la methode CreateComponent<T>() le T correspond a une classe qui à herite de component
	GetComponent fonctionne sur le meme principe*/
private:
	std::vector<Component*> components;
	int calque = 0;
	int id = 0;
protected:
	std::string name;
	Transform transform;
	Scene* scene = nullptr;
public:
	bool destroyed = false;
	GameObject(){ }
	GameObject(std::string _name) { name = _name; }
	GameObject(int ID) { id = ID; }
	GameObject(std::string _name, int ID);
	void SetName(std::string _name) { name = _name; }
	void SetId(int ID) { id = ID; }
	void SetPosition(float x, float y) { transform.position_x = x; transform.position_y = y; };
	void SetPosition(sf::Vector2f pos) { transform.position_x = pos.x; transform.position_y = pos.y; };
	void Move(float x, float y) { transform.position_x += x; transform.position_y += y; }
	void Move(sf::Vector2f pos) { transform.position_x += pos.x; transform.position_y += pos.y; }
	void SetScale(float x, float y) { transform.scale_x = x; transform.scale_y = y; };
	void SetRotation(float angle) { transform.rotation = angle; };
	void Rotate(float angle) { transform.rotation += angle; }
	void SetCalque(int _calque) { calque = _calque; }
	void SetScene(Scene* newScene) { scene = newScene; }
	sf::Vector2f GetPosition() { return { transform.position_x,transform.position_y }; };
	sf::Vector2f GetScale() { return { transform.scale_x,transform.scale_y }; };
	float GetRotation() { return transform.rotation; };
	int GetCalque() { return calque; }
	std::string GetName() { return name; }
	int GetId() { return id; }
	Scene* GetScene() { return scene; }
	void Start();
	void Update(TimeModule* timeModule);
	void Render(WindowModule* window);
	void Destroy();
	template<typename T, typename... Param>
	T* CreateComponent(Param... parameters)
	{
		T* component = new T(parameters...);
		component->SetOwner(this);
		components.push_back(component);
		return component;
	}

	template<typename T>
	T* GetComponent() {
		for (Component* component : components)
		{
			T* result = dynamic_cast<T*>(component);
			if (result != nullptr)
				return result;
		}
		return nullptr;
	}

};
