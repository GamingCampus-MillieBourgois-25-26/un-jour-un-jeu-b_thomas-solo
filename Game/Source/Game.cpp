#include <Engine.h>
#include <SceneModule.h>
#include <RessourceModule.h>
#include "Include/BulletHell/BulletHell.h"
#include <Include/SceneMenu.h>

int main()
{
    srand((unsigned int)time(0));
    Engine* engine = Engine::GetInstance();
    engine->Init();
    ModuleManager* moduleManger = engine->GetModuleManager();
    WindowModule* windowModule = moduleManger->GetModule<WindowModule>();
    windowModule->SetWindowSize({ 800,800 });
    windowModule->SetWindowName("window");

    RessourceModule* ressourceModule = moduleManger->GetModule<RessourceModule>();
    ressourceModule->AddTexture("BulletHellPlayer","Assets/BulletHell/playerShip1_green.png");
    ressourceModule->AddTexture("BulletHellEnemy","Assets/BulletHell/playerShip3_red.png");
    ressourceModule->AddTexture("BulletHellBullet","Assets/BulletHell/laserRed01.png");
    ressourceModule->AddTexture("BulletHellRBullet","Assets/BulletHell/laserRed01.png");

    SceneModule* sceneModule = moduleManger->GetModule<SceneModule>();
    sceneModule->AddScene<BulletHell::BulletHell>("BulletHell");
    sceneModule->AddScene<SceneMenu>("SceneMenu");
    sceneModule->SetMain(sceneModule->GetScene("SceneMenu"));

    engine->Start();
    engine->Run();
    return 0;
}