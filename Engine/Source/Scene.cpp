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
	while (calque >= gameObjects.size()) {
		AddCalque();
	}
	gameObject->SetCalque(calque);
	gameObject->SetScene(this);
	pendingObjects.push_back(gameObject);
}

void Scene::DestroyObject(GameObject* gameObject)
{
	if (gameObject->destroyed) {
		return;
	}
	int calque = gameObject->GetCalque();
	gameObject->destroyed = true;
	pendingDestroy.push_back(gameObject);
}

void Scene::AddCalque()
{
	std::vector<GameObject*> calque;
	gameObjects.push_back(calque);
}

void Scene::FlushPending()
{
	for(GameObject* object : pendingObjects)
	{
		gameObjects[object->GetCalque()].push_back(object);
	}
	for(GameObject* object : pendingObjects)
	{
		object->Awake();
		object->Start();
	}
	pendingObjects.clear();
	

	for (GameObject* obj : pendingDestroy)
	{
		obj->Destroy();
		auto it = std::find(gameObjects[obj->GetCalque()].begin(), gameObjects[obj->GetCalque()].end(), obj);
		if (it != gameObjects[obj->GetCalque()].end())
		{
			gameObjects[obj->GetCalque()].erase(it);
		}

		delete obj;
	}
	pendingDestroy.clear();	
	
}

