#pragma once
#include "Component.h"
#include <SceneModule.h>
class LastSceneBackground : public Component
{
public:
	SceneModule* sceneModule = nullptr;
	void Start()override;
	void Render(WindowModule* windowModule)override;
};

