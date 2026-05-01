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
	camera->UseView();
	player->SetPosition(400, 1000);
	player->SetId(1);
	std::vector<sf::Vector2f> target({ sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 300.f) });
	EnemyBase* enemy = new EnemyBase(ressource, target);
	enemy->SetPosition(100, 100);
	enemy->SetId(2);

	EnemySniper* enemy2 = new EnemySniper(ressource, {600, 100}, {600,300});
	enemy2->SetPosition(600, 100);
	enemy2->SetId(2);

	Obstacle* obstacle = new Obstacle(ressource->GetTexture("obstacle"));
	obstacle->SetPosition(500,100);

	VictoryPoint* victory = new VictoryPoint();
	victory->SetPosition(600, 600);

	AddGameObject(player, 0);
	AddGameObject(enemy, 0);
	AddGameObject(enemy2, 0);
	AddGameObject(victory, 0);
	AddGameObject(obstacle, 0);
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

