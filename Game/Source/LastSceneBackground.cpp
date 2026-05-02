#include <Include/LastSceneBackground.h>
#include <Engine.h>

void LastSceneBackground::Start()
{
	sceneModule = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>();
}

void LastSceneBackground::Render(WindowModule* windowModule)
{
	sceneModule->GetLastScene()->Render(windowModule);
}
