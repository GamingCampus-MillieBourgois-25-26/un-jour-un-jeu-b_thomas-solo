#include <Include/BulletHell/Player.h>
#include <Engine.h>
#include "InputModule.h"
#include <SpriteRender.h>
#include <RessourceModule.h>

BulletHell::Player::Player(RessourceModule* ressource)
{
	CreateComponent<InputPlayer>();
	collisionBox = CreateComponent<CollisionBoxPlayer>();
	collisionBox->Init(sf::Vector2f(75, 50));
	CreateComponent<SpriteRender>(ressource->GetTexture("BulletHellPlayer"), sf::IntRect({ 0,0 },{99,75}));
	CreateComponent<Invulnerability>();
}

void BulletHell::InputPlayer::Start()
{
	input = Engine::GetInstance()->GetModuleManager()->GetModule<InputModule>();
	player = static_cast<Player*>(owner);
}

void BulletHell::InputPlayer::Update(TimeModule* timeModule)
{
	sf::Vector2f mousePos = input->GetMousePosition();
	mousePos.x = std::clamp(mousePos.x, 0.f, static_cast<float>(input->GetWindowSize().x));
	mousePos.y = std::clamp(mousePos.y, 0.f, static_cast<float>(input->GetWindowSize().y));
	owner->SetPosition(mousePos);
}

void BulletHell::CollisionBoxPlayer::Start()
{
	CollisionBox::Start();
	invulnerability = owner->GetComponent<Invulnerability>();
}

void BulletHell::CollisionBoxPlayer::Collide(CollisionBox* other)
{
	if(!invulnerability->Invicible)
	{
		std::cout << "oui";
		invulnerability->Invicible = true;
		Player* player = static_cast<Player*>(owner);
		player->life--;
	}
}

void BulletHell::Invulnerability::Update(TimeModule* timeModule)
{
	if (Invicible) {
		if (timerInvincible > 0) {
			timerInvincible -= timeModule->GetDeltaTime();
			blinkingTimer -= timeModule->GetDeltaTime();
			if (blinkingTimer < 0) {
				blinkingTimer = blinkingTimerMax;
				SpriteRender* sprite = owner->GetComponent<SpriteRender>();
			
				sf::Color color = sprite->sprite.getColor();
				color.a = 255 - color.a;
				sprite->sprite.setColor(color);

			}
		}
		else {
			Invicible = false;
			timerInvincible = timerInvincibleMax;
			blinkingTimer = 0;
			SpriteRender* sprite = owner->GetComponent<SpriteRender>();
			sf::Color color = sprite->sprite.getColor();
			color.a = 255;
			sprite->sprite.setColor(color);
		}
	}
}
