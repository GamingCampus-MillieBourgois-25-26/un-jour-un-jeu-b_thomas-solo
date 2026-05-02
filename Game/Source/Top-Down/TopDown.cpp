#include <Include/Top-Down/TopDown.h>
#include <Include/Top-Down/PlayerTopDown.h>
#include <Include/Top-Down/EnemyTopDown.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/Top-Down/VictoryPoint.h>
#include <Include/Top-Down/Obstacle.h>

TopDown::TopDown::TopDown()
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	Player* player = new Player(ressource);
	Camera* camera = player->CreateComponent<Camera>(sf::FloatRect({0,0},{800,800}), sf::Vector2f(400,400), sf::Vector2f(400,1600));
	player->SetPosition(400, 1900);
	camera->UseView();
	player->SetRotation(-90);
	player->SetId(1);

	std::vector<sf::Vector2f> target({ sf::Vector2f(100, 1250), sf::Vector2f(500, 1250) });
	EnemyBase* enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(100, 1250);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	target = std::vector<sf::Vector2f>({ sf::Vector2f(600, 1100), sf::Vector2f(600, 1400) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(600, 1100);
	enemy->SetRotation(90);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	target = std::vector<sf::Vector2f>({ sf::Vector2f(100, 800), sf::Vector2f(700, 800) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(100, 800);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	target = std::vector<sf::Vector2f>({ sf::Vector2f(700, 300), sf::Vector2f(700, 500) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(700, 300);
	enemy->SetRotation(90);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	target = std::vector<sf::Vector2f>({ sf::Vector2f(400, 300), sf::Vector2f(400, 500) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(400, 300);
	enemy->SetRotation(90);
	enemy->SetId(2);
	AddGameObject(enemy, 0);
	target = std::vector<sf::Vector2f>({ sf::Vector2f(100, 300), sf::Vector2f(100, 500) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(100, 300);
	enemy->SetRotation(90);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	target = std::vector<sf::Vector2f>({ sf::Vector2f(700, 900), sf::Vector2f(100, 900) });
	enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(700, 900);
	enemy->SetId(2);
	AddGameObject(enemy, 0);

	EnemySniper* enemy2 = new EnemySniper(ressource, {300, 1100}, {500,1100});
	enemy2->SetPosition(300, 1100);
	enemy2->SetId(2);
	AddGameObject(enemy2, 0);

	enemy2 = new EnemySniper(ressource, { 350, 600 }, { 150, 600 });
	enemy2->SetPosition(350, 600);
	enemy2->SetRotation(180);
	enemy2->SetId(2);
	AddGameObject(enemy2, 0);

	enemy2 = new EnemySniper(ressource, { 450, 600 }, { 650,600 });
	enemy2->SetPosition(450, 600);
	enemy2->SetId(2);
	AddGameObject(enemy2, 0);

	Obstacle* obstacle = new Obstacle(ressource->GetTexture("obstacle"));
	obstacle->SetPosition(300,1175);
	AddGameObject(obstacle, 0);

	obstacle = new Obstacle(ressource->GetTexture("obstacle"));
	obstacle->SetPosition(450,675);
	AddGameObject(obstacle, 0);

	obstacle = new Obstacle(ressource->GetTexture("obstacle"));
	obstacle->SetPosition(350, 675);
	AddGameObject(obstacle, 0);

	VictoryPoint* victory = new VictoryPoint();
	victory->SetPosition(400, 100);

	GameObject* hud = new GameObject();
	hud->CreateComponent<ReloadHud>(sf::Vector2f(20, 740), player);
	AddGameObject(hud, 2);
	AddGameObject(player, 1);
	AddGameObject(victory, 0);
}
TopDown::TopDown* TopDown::TopDown::Reset()
{
	return new TopDown();
}
TopDown::Tank::Tank(sf::Texture* texBarrel, sf::Texture* texFrame)
{
	CreateComponent<TankRender>(texBarrel, texFrame);
}

TopDown::TankRender::TankRender(sf::Texture *texBarrel, sf::Texture *texFrame)
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	barrel = new SpriteRender(texBarrel, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(texBarrel->getSize())));
	barrel->sprite.setOrigin({ 8, 0 });
	barrel->offsetRotation = 90;
	frame = new SpriteRender(texFrame, sf::IntRect({ 0,0 }, static_cast<sf::Vector2i>(texFrame->getSize())));
	frame->offsetRotation = 90;
}

void TopDown::TankRender::Start()
{
	tank = static_cast<Tank*>(owner);
	barrel->owner = owner;
	frame->owner = owner;
}

void TopDown::TankRender::Update(TimeModule* timeModule)
{
	barrel->offsetRotation = tank->rotationBarrel - 90;
	barrel->Update(timeModule);
	frame->Update(timeModule);
}

void TopDown::TankRender::Render(WindowModule* windowModule)
{
	frame->Render(windowModule);
	barrel->Render(windowModule);
}

void TopDown::TankRender::Destroy()
{
	delete barrel;
	delete frame;
}

