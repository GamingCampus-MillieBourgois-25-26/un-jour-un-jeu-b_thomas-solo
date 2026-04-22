#pragma once
#include "ModuleManager.h"
class ModuleManager;
class Module
{
	/*Un module gere une specificite du moteur comme les scenes le temps la fenetre de jeu*/
public:
	void SetModuleManager(ModuleManager* _moduleManager) { moduleManager = _moduleManager; }
	virtual void Awake() {};
	virtual void Start() {};
	virtual void Update() {};
	virtual void Clear() {};
	virtual void Render() {};
	virtual void Display() {};
	virtual void Destroy() {};
	ModuleManager* GetModuleManager() {
		return moduleManager;
	}
protected:
	ModuleManager* moduleManager;
};

