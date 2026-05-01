#include "pch.h"
#include "Include/Module/CollisionModule.h"
#include "Include/Component/CollisionBox.h"

void CollisionModule::Awake()
{
	sceneModule = moduleManager->GetModule<SceneModule>();

}

void CollisionModule::Update()
{
	/*Prends une colisionBox et regarde toute les autre colisionBox pour voir s'ils se touchent*/
	for(CollisionBox* collisonBoxI : colisionBoxs)
	{
		for (CollisionBox* collisionBoxJ : colisionBoxs)
		{
			if (collisonBoxI != collisionBoxJ) {
				if (collisonBoxI->IsColliding(collisionBoxJ)) {
					collisonBoxI->Collide(collisionBoxJ);
				}
			}
		}
	}
	colisionBoxs.clear();
}