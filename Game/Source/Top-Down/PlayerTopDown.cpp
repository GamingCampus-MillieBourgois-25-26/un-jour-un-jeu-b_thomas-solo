#include <Include/Top-Down/PlayerTopDown.h>
#include <RessourceModule.h>
#include <Engine.h>
#include <Include/Top-Down/ProjectileTopDown.h>

TopDown::Player::Player(RessourceModule* ressourceModule): Tank(ressourceModule->GetTexture("TopDownPlayerBarrel"), ressourceModule->GetTexture("TopDownPlayerFrame"))
{
	CreateComponent<PlayerInput>();
	CollisionBoxPlayer* box = CreateComponent<CollisionBoxPlayer>();
	CreateComponent<ReloadHud>(sf::Vector2f(20, 740));
	box->Init({ 40,40 });
	speed = 90;
	rotationSpeed = 100;
	rotationBarrelSpeed = 180;
	
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

	sf::Vector2f pos = owner->GetPosition();
	pos.x = std::clamp(pos.x, 0.f, 800.f);
	owner->SetPosition(pos);

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
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	Projectile* projectile = new Projectile(ressource->GetTexture("TopDownPlayerBullet"), player);
	projectile->SetPosition(owner->GetPosition());
	projectile->SetRotation(owner->GetRotation() + player->rotationBarrel);
	owner->GetScene()->AddGameObject(projectile, owner->GetCalque());
}

void TopDown::CollisionBoxPlayer::Collide(CollisionBox* other) {
	if (other->owner->GetId() == 3) {
		Projectile* projectile = static_cast<Projectile*>(other->owner);
		if (projectile->owner->GetId() == 2) {
			std::cout << "degat" << std::endl;
			projectile->GetScene()->DestroyObject(projectile);
		}
	}
}
TopDown::Camera::Camera(sf::FloatRect rect, sf::Vector2f _clampX, sf::Vector2f _clampY): view(rect), clampX(_clampX), clampY(_clampY)
{
}



void TopDown::Camera::Update(TimeModule* timeModule)
{
	sf::Vector2f cameraPos = owner->GetPosition();
	cameraPos.x = std::clamp(cameraPos.x, clampX.x, clampX.y);
	cameraPos.y = std::clamp(cameraPos.y, clampY.x, clampY.y);
	view.setCenter(cameraPos);
}

void TopDown::Camera::Render(WindowModule* windowModule)
{
	if (isUseing)
		windowModule->GetWindow()->setView(view);
}

void TopDown::Camera::UseView()
{
	isUseing = true;
}

TopDown::ReloadHud::ReloadHud(sf::Vector2f _pos):pos(_pos)
{
	
	rectBg.setFillColor(sf::Color::Transparent);
	rectBg.setOutlineColor(sf::Color::White);
	rectBg.setOutlineThickness(-1);
	rectBg.setSize({ 80,20 });
	rectReload.setFillColor(sf::Color::Yellow);
}

void TopDown::ReloadHud::Start()
{
	player = static_cast<Player*>(owner);
}

void TopDown::ReloadHud::Update(TimeModule* timeModule)
{
	float factor = 1 - player->reloadTime / player->reloadTimeMax;
	factor = std::clamp(factor, 0.f, 1.f);
	rectReload.setSize({ factor * 80.f, 20.f });
}

void TopDown::ReloadHud::Render(WindowModule* windowModule)
{
	sf::Vector2f cameraPos = windowModule->GetWindow()->getView().getCenter() - windowModule->GetWindow()->getView().getSize() / 2.f;
	rectBg.setPosition(pos + cameraPos);
	rectReload.setPosition(pos + cameraPos);
	windowModule->GetWindow()->draw(rectReload);
	windowModule->GetWindow()->draw(rectBg);
}
