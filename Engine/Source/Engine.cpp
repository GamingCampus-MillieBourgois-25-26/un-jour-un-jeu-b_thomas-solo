#include "pch.h"
#include "Include/Engine.h"
#include <iostream>

Engine* Engine::instance = nullptr;
void Engine::Init() {
	/*Prepare le moteur en creant les modules de bases et en faisant les premieres initialisations*/
	moduleManager->CreateDefaultModule();
	moduleManager->Awake();
}
void Engine::Start() {
	moduleManager->Start();
}
void Engine::Run() {
	while (!shouldQuit) {
		
		moduleManager->Clear();
		moduleManager->Update();
		moduleManager->Render();
		moduleManager->Display();
	}
	moduleManager->Destroy();
}