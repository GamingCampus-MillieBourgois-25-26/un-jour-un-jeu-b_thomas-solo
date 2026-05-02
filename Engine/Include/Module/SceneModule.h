#pragma once
#include "Include/Module.h"
#include "vector"
#include "Include/Scene.h"
#include "WindowModule.h"
#include "TimeModule.h"
#include <iostream>
class SceneModule :public Module
{
	/*gere les scenes et affiche et update uniqument la mainScene*/
public:
	void Awake()override;
	void Start()override;
	void Update()override;
	void Render()override;
	void Destroy()override;
	template<typename T>
	T* AddScene(std::string name) {
		for (Scene* scene : scenes) {
			if (scene->GetName() == name)
				DestroyScene(scene);
		}
		T* newScene = new T();
		newScene->SetName(name);
		if (newScene != nullptr) {
			scenes.push_back(newScene);
			newScene->Start();
		}
		return newScene;
	}
	Scene* AddScene(Scene* scene) {
		Scene* newScene = scene->Reset();
		newScene->SetName(scene->GetName());
		DestroyScene(scene);
		scenes.push_back(newScene);
		newScene->Start();
		return newScene;

	}
	void DestroyScene(Scene* scene) {
		scene->Destroy();
		auto it = std::find(scenes.begin(), scenes.end(), scene);
		if (it != scenes.end())
		{
				
			scenes.erase(it);
		}
		delete scene;
	}
	
	void SetMain(Scene* scene) {
		lastScene = mainScene;
		if (scene == nullptr) {
			std::cout << "scene == nullptr";
		}
			mainScene = scene;
	}
	Scene* GetScene(std::string name) {
		for (Scene* scene : scenes) {
			if (scene->GetName() == name) {
				return scene;
			}
		}
		return nullptr;
	}
	std::vector<Scene*> GetScenes() {
		return scenes;
	}
	Scene* GetMainScene() { return mainScene; }
	Scene* GetLastScene() { return lastScene; }
private:
	WindowModule* windowModule = nullptr;
	TimeModule* timeModule = nullptr;

	Scene* mainScene = nullptr;
	Scene* lastScene = nullptr;
	std::vector<Scene*>scenes;
};

