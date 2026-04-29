#include <Engine.h>
#include <SceneModule.h>
#include <RessourceModule.h>
#include "Include/BulletHell/BulletHell.h"
#include <Include/SceneMenu.h>
#include <Include/TowerDefense/TowerDefense.h>
#include <Include/Clicker/Clicker.h>
#include <Include/Match3/Match3.h>
#include <Include/Top-Down/TopDown.h>


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
    ressourceModule->AddFont("font", "Assets/font/Kenney Pixel Square.ttf");

    ressourceModule->AddTexture("BulletHellPlayer","Assets/BulletHell/playerShip1_green.png");
    ressourceModule->AddTexture("BulletHellEnemy","Assets/BulletHell/playerShip3_red.png");
    ressourceModule->AddTexture("BulletHellBullet","Assets/BulletHell/laserRed01.png");
    ressourceModule->AddTexture("BulletHellRBullet","Assets/BulletHell/laserRed01.png");

    ressourceModule->AddTexture("TowerDefensePasLourd", "Assets/TowerDefense/towerDefense_tile245.png");
    ressourceModule->AddTexture("TowerDefenseLourd", "Assets/TowerDefense/towerDefense_tile270.png");
    ressourceModule->AddTexture("TowerDefenseTropLourd", "Assets/TowerDefense/towerDefense_tile271.png");

    ressourceModule->AddTexture("TopDownBarrel", "Assets/Top-Down/barrelGreen.png");
    ressourceModule->AddTexture("TopDownFrame", "Assets/Top-Down/tankGreen.png");
    ressourceModule->AddTexture("TopDownBullet", "Assets/Top-Down/bulletGreen.png");

    SceneModule* sceneModule = moduleManger->GetModule<SceneModule>();
    sceneModule->AddScene<BulletHell::BulletHell>("BulletHell");
    sceneModule->AddScene<TowerDefense::TowerDefense>("TowerDefense");
    sceneModule->AddScene<Clicker::Clicker>("Clicker");
    sceneModule->AddScene<Match3::Match3>("Match3");
    sceneModule->AddScene<TopDown::TopDown>("TopDown");
    sceneModule->AddScene<SceneMenu>("SceneMenu");
    sceneModule->SetMain(sceneModule->GetScene("TopDown"));

    engine->Start();
    engine->Run();
    return 0;
}