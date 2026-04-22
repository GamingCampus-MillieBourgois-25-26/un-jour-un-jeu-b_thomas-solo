#include "pch.h"
#include "Include/Scene.h"
#include "Include/GameObject.h"
#include <iostream>

void Scene::Start() {
	for (std::vector<GameObject*> calque : gameObjects) {
		for (GameObject* gameObject : calque) {
			gameObject->Start();
		}
	}
}
void Scene::Update(TimeModule* timeModule) {
	for (std::vector<GameObject*> calque : gameObjects) {
		//std::cout << "( ";
		for (GameObject* gameObject : calque) {
			if(!gameObject->destroyed)
				gameObject->Update(timeModule);
		}
		//std::cout << " )";
	}
	//std::cout << std::endl;
	FlushPending();
}
void Scene::Render(WindowModule* windowModule) {
	for (std::vector<GameObject*> calque : gameObjects) {
		for (GameObject* gameObject : calque) {
			gameObject->Render(windowModule);
		}
	}
}
void Scene::Destroy() {
	FlushPending();
	for (std::vector<GameObject*> calque : gameObjects) {
		for (GameObject* gameObject : calque) {
			gameObject->Destroy();
			delete gameObject;
		}
	}
	gameObjects.clear();
}
GameObject* Scene::GetGameObject(std::string name)
{
	for (std::vector<GameObject*> calque : gameObjects) {
		for (GameObject* obj : calque) {
			if (obj->GetName() == name) {
				return obj;
			}
		}
	}
	return nullptr;
}
GameObject* Scene::GetGameObject(int id)
{
	for (std::vector<GameObject*> calque : gameObjects) {
		for (GameObject* obj : calque) {
			if (obj->GetId() == id) {
				return obj;
			}
		}
	}
	return nullptr;
}
void Scene::AddGameObject(GameObject* gameObject, int calque)
{
	gameObject->SetCalque(calque);
	gameObject->SetScene(this);
	pendingObjects[calque].push_back(gameObject);
}

void Scene::DestroyObject(GameObject* gameObject)
{
	if (gameObject->destroyed) {
		return;
	}
	int calque = gameObject->GetCalque();
	gameObject->destroyed = true;
	pendingDestroy[calque].push_back(gameObject);
}

void Scene::AddCalque()
{
	std::vector<GameObject*> calque;
	gameObjects.push_back(calque);
	pendingObjects.push_back(calque);
	pendingDestroy.push_back(calque);
}

void Scene::FlushPending()
{
	for (int i = 0; i < gameObjects.size(); i++) {
		for(GameObject* object : pendingObjects[i])
		{
			gameObjects[i].push_back(object);
			object->Start();
		}
		pendingObjects[i].clear();
	}
	for (int i = 0; i < gameObjects.size(); i++) {

		for (GameObject* obj : pendingDestroy[i])
		{
			obj->Destroy();
			auto it = std::find(gameObjects[i].begin(), gameObjects[i].end(), obj);
			if (it != gameObjects[i].end())
			{
				gameObjects[i].erase(it);
			}

			delete obj;
		}
		pendingDestroy[i].clear();	
	}
}

