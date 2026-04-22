#include "pch.h"
#include "Include/ModuleManager.h"
#include "Include/Module/InputModule.h"
#include "Include/Module/SceneModule.h"
#include "Include/Module/WindowModule.h"
#include "Include/Module/TimeModule.h"
#include "Include/Module/ColisionModule.h"
#include "Include/Module/RessourceModule.h"


void ModuleManager::CreateDefaultModule()
{
	CreateModule<SceneModule>();
	CreateModule<InputModule>();
	CreateModule<WindowModule>();
	CreateModule<TimeModule>();
	CreateModule<ColisionModule>();
	CreateModule<RessourceModule>();
}
void ModuleManager::Awake() {
	for (Module* module : modules) {
		module->Awake();
	}
}
void ModuleManager::Start() {
	for (Module* module : modules) {
		module->Start();
	}
}
void ModuleManager::Update() {
	for (Module* module : modules) {
		module->Update();
	}
}
void ModuleManager::Clear()
{
	for (Module* module : modules) {
		module->Clear();
	}
}
void ModuleManager::Render() {
	for (Module* module : modules) {
		module->Render();
	}
}
void ModuleManager::Display()
{
	for (Module* module : modules) {
		module->Display();
	}
}
void ModuleManager::Destroy() {
	for (Module* module : modules) {
		module->Destroy();
		delete module;
	}
	modules.clear();
}