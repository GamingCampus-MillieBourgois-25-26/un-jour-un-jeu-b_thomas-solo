#pragma once
#include "Scene.h"
#include "ModuleManager.h"
#include "SFML/Graphics.hpp"
class Engine {
public:
	static Engine* GetInstance() {
		/*Singleton d'Engine*/
		if(instance == nullptr)
		{
			instance = new Engine();
		}

		return instance;
	}
	void Init();	
	void Start();	
	void Run();
	void Quit() { shouldQuit = true; }
	ModuleManager* GetModuleManager() { return moduleManager; }
	static Engine* instance;

private:

	ModuleManager* moduleManager = new ModuleManager;
	bool shouldQuit = false;
	Engine() { }
};


