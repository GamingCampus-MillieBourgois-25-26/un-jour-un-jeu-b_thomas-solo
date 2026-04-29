#include <Include/Top-Down/TopDown.h>
#include <Include/Top-Down/PlayerTopDown.h>
#include <Include/Top-Down/EnemyTopDown.h>

TopDown::TopDown::TopDown()
{
	Player* player = new Player();
	player->SetPosition(400, 400);

	Enemy* enemy = new Enemy();
	enemy->SetPosition(100, 100);
	AddGameObject(player, 0);
	AddGameObject(enemy, 0);
}
