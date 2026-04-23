#pragma once
#include "Include/Module.h"
#include "Include/Module/SceneModule.h"
#include "Include/Component/CollisionBox.h"

class CollisionBox;
class CollisionModule : public Module
{
	/*Un Module de base du moteur
	il s'occupe de verifier toute les boites de colision qui se trouve dans la scene*/
public:
	void Awake()override;
	void Update()override;
	std::vector<CollisionBox*>colisionBoxs;
private:
	SceneModule* sceneModule = nullptr;
};

