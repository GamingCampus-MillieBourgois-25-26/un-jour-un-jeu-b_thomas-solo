#include "pch.h"
#include "Include/Module/ColisionModule.h"
#include "Include/Component/ColisionBox.h"

void ColisionModule::Awake()
{
	sceneModule = moduleManager->GetModule<SceneModule>();

}

void ColisionModule::Update()
{
	/*Prends une colisionBox et regarde toute les autre colisionBox pour voir s'ils se touchent*/
	for(ColisionBox* collisonBoxI : colisionBoxs)
	{
		for (ColisionBox* collisionBoxJ : colisionBoxs) {
			if (collisonBoxI != collisionBoxJ) {
				if (collisonBoxI->IsColliding(*collisionBoxJ)) {
					collisonBoxI->Collide(collisionBoxJ);
				}
			}
		}
	}
	colisionBoxs.clear();
}