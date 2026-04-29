#include <Include/Top-Down/PlayerTopDown.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/Top-Down/ProjectileTopDown.h>

TopDown::Player::Player()
{
	CreateComponent<PlayerRender>();
	CreateComponent<PlayerInput>();
}

TopDown::PlayerRender::PlayerRender()
{
	RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	barrel = new SpriteRender(ressourceModule->GetTexture("TopDownBarrel"),sf::IntRect({0,0},{16,50}));
	barrel->sprite.setOrigin({ 8, 0 });
	barrel->offsetRotation = 90;
	frame = new SpriteRender(ressourceModule->GetTexture("TopDownFrame"), sf::IntRect({ 0,0 }, { 75,70 }));
	frame->offsetRotation = 90;
}

void TopDown::PlayerRender::Start()
{
	player = static_cast<Player*>(owner);
	barrel->owner = owner;
	frame->owner = owner;
}

void TopDown::PlayerRender::Update(TimeModule* timeModule)
{
	barrel->offsetRotation = player->rotationBarrel - 90;
	barrel->Update(timeModule);
	frame->Update(timeModule);
}

void TopDown::PlayerRender::Render(WindowModule* windowModule)
{
	frame->Render(windowModule);
	barrel->Render(windowModule);
}

void TopDown::PlayerRender::Destroy()
{
	delete barrel;
	delete frame;
}

void TopDown::PlayerInput::Start()
{
	input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
	player = static_cast<Player*>(owner);
}

void TopDown::PlayerInput::Update(TimeModule* timeModule)
{
	player->reloadTime -= timeModule->GetDeltaTime();
	if (input->GetKeyDown(sf::Keyboard::Key::Z)) {
		MoveForward(player->speed * timeModule->GetDeltaTime());
	}
	if (input->GetKeyDown(sf::Keyboard::Key::S)) {
		MoveForward(-player->speed * timeModule->GetDeltaTime());
	}
	if (input->GetKeyDown(sf::Keyboard::Key::Q)) {
		owner->Rotate(-player->rotationSpeed * timeModule->GetDeltaTime());
	}
	if (input->GetKeyDown(sf::Keyboard::Key::D)) {
		owner->Rotate(player->rotationSpeed * timeModule->GetDeltaTime());
	}
	if (input->GetMouseButtonDown(sf::Mouse::Button::Left))
	{
		if (player->reloadTime <= 0) {
			player->reloadTime = player->reloadTimeMax;
			Shoot();
		}
	}
	while (player->rotationBarrel >= 360 || player->rotationBarrel < 0) {
		if (player->rotationBarrel < 0)
			player->rotationBarrel += 360;
		if (player->rotationBarrel >= 360)
			player->rotationBarrel -= 360;
	}
	RotateBarrel(player->rotationBarrelSpeed * timeModule->GetDeltaTime());
}

void TopDown::PlayerInput::MoveForward(float speed)
{
	sf::Vector2f direction(cos(owner->GetRotation() * 3.141/180), sin(owner->GetRotation() * 3.141 / 180));
	owner->Move(direction * speed);
}

void TopDown::PlayerInput::RotateBarrel(float speedRotation)
{
	sf::Vector2f delta = input->GetMousePosition() - owner->GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if(distance != 0)
	{
		sf::Vector2f direction = delta / distance;
		float angle = atan2(direction.y, direction.x) * 180/3.141;
		float rotation = player->rotationBarrel + owner->GetRotation();
		float angleDiff = rotation - angle;
		while (angleDiff >= 180 || angleDiff < -180) {
			if (angleDiff < -180)
				angleDiff += 360;
			if (angleDiff >= 180)
				angleDiff -= 360;
		}
		
		if (abs(angleDiff) <= speedRotation)
			player->rotationBarrel = angle - owner->GetRotation();
		else {
			if (angleDiff < 0)
				player->rotationBarrel += speedRotation;
			else
				player->rotationBarrel -= speedRotation;
			
		}
	}
}

void TopDown::PlayerInput::Shoot()
{
	Projectile* projectile = new Projectile();
	projectile->SetPosition(owner->GetPosition());
	projectile->SetRotation(owner->GetRotation() + player->rotationBarrel);
	owner->GetScene()->AddGameObject(projectile, owner->GetCalque());
}
