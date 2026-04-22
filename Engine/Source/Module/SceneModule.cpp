#include "pch.h"
#include "Include/Module/SceneModule.h"

void SceneModule::Awake()
{
	timeModule = moduleManager->GetModule<TimeModule>();
	windowModule = moduleManager->GetModule<WindowModule>();
}

void SceneModule::Start()
{
	for (Scene* scene : scenes) {
		scene->Start();
	}
}

void SceneModule::Update()
{
	mainScene->Update(timeModule);
}

void SceneModule::Render()
{
	mainScene->Render(windowModule);
}

void SceneModule::Destroy()
{
	for (Scene* scene : scenes) {
		scene->Destroy();
		delete scene;
	}
	scenes.clear();
}
