#pragma once
#include <vector>
#include "Module.h"
class Module;
class ModuleManager
{
	/*gere tout les modules initialise dans le moteur et permet aussi un pont entre les modules*/
public:
	void CreateDefaultModule();
	void Awake();
	void Start();
	void Update();
	void Clear();
	void Render();
	void Display();
	void Destroy();
	template<typename T>
	T* CreateModule() {
		T* newModule = new T();
		newModule->SetModuleManager(this);
		modules.push_back(newModule);
		return newModule;
		}
	template<typename T>
	T* GetModule() {
		for (Module* module : modules) {
			T* result = dynamic_cast<T*>(module);
			if (result != nullptr) {
				return result;
			}
		}
		return nullptr;
	}
private:
	std::vector<Module*>modules;
};

