#include <Include/BulletHell/BulletHell.h>
#include <Include/BulletHell/Player.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/BulletHell/Projectile.h>
#include <Include/BulletHell/EnemyBulletHell.h>

BulletHell::BulletHell::BulletHell()
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	Player* player = new Player(ressourceModule);
	player->SetScale(0.5, 0.5);
	Enemy* enemy = new Enemy(ressourceModule);
	enemy->SetRotation(90);
	enemy->SetPosition(100,100);
	AddCalque();
	AddGameObject(player,0);
	AddGameObject(enemy,0);
}

BulletHell::BulletHell* BulletHell::BulletHell::Reset()
{
	return new BulletHell();
}
