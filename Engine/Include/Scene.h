#pragma once
#include <vector>
#include <string>
class GameObject;
class TimeModule;
class WindowModule;
class Scene
{
	/*les secene contient des gameObjects les scenes fonctionnes avec des calques pour pouvoir donner un ordre d'affichage*/
public:
	void Start();
	void Update(TimeModule* deltaTime);
	void Render(WindowModule* window);
	void Destroy();
	std::string GetName() { return name; }
	GameObject* GetGameObject(std::string name);
	GameObject* GetGameObject(int id);
	std::vector<std::vector<GameObject*>> GetGameObjects() { return gameObjects; }
	void SetName(std::string _name) { name = _name; }
	void AddGameObject(GameObject* gameObject, int calque);
	void DestroyObject(GameObject* gameObject);
	void AddCalque();

protected:
	std::vector<std::vector<GameObject*>> pendingObjects;
	std::vector<std::vector<GameObject*>> pendingDestroy;

	void FlushPending();
private:
	std::vector<std::vector<GameObject*>> gameObjects;
	std::string name;
};

