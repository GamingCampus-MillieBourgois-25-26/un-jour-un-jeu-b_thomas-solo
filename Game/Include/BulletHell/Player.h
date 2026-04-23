#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Component/CollisionBox.h"
class InputModule;
class RessourceModule;
namespace BulletHell
{
	class Invulnerability : public Component {
	public:
		float timerInvincibleMax = 2;
		float blinkingTimerMax = 0.2;
		float timerInvincible = timerInvincibleMax;
		float blinkingTimer = 0;
		bool Invicible = false;
		void Update(TimeModule* timeModule)override;
	};
	class CollisionBoxPlayer : public CollisionBox {
	public:
		Invulnerability* invulnerability = nullptr;
		void Start()override;
		void Collide(CollisionBox* other)override;
	};
	class Player : public GameObject  
	{
	public:
		int life = 3;
		CollisionBoxPlayer* collisionBox = nullptr;
		Player(RessourceModule* ressource);
	};

	class InputPlayer : public Component {
	public:
		void Start()override;
		void Update(TimeModule* timeModule)override;
	private:
		Player* player = nullptr;
		InputModule* input = nullptr;

	};
}