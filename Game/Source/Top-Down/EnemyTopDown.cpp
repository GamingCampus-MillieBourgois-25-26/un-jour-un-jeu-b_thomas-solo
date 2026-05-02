#include <Include/Top-Down/EnemyTopDown.h>
#include <Engine.h>
#include <SceneModule.h>
#include <Include/BasicBox.h>
#include <Include/Top-Down/ProjectileTopDown.h>
#include "Include/Top-Down/Smoke.h"


TopDown::Enemy::Enemy(sf::Texture* texBarrel, sf::Texture* texFrame): Tank(texBarrel, texFrame)
{
}

TopDown::EnemyBase::EnemyBase(RessourceModule* ressourceModule, std::vector<sf::Vector2f>patrolPoints): Enemy(ressourceModule->GetTexture("TopDownBarrelRed"), ressourceModule->GetTexture("TopDownFrameRed"))
{
	speed = 55;
	rotationBarrelSpeed = 40;
	CreateComponent<EnemyBaseAi>();
	EnemyCollision* box = CreateComponent<EnemyCollision>();
	box->Init({ 40,40 });

	FSM* fsm = CreateComponent<FSM>();
	Patrol* patrol = new Patrol(patrolPoints);
	patrol->condition = [](GameObject* owner, State* currentState) {
		sf::Vector2f playerPos = owner->GetScene()->GetGameObject(1)->GetPosition();
		sf::Vector2f delta = playerPos - owner->GetPosition();
		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance <= 250)
			return true;
		else
			return false;
		};
	Chase* chase = new Chase();
	chase->condition = [](GameObject* owner, State* currentState) {
		sf::Vector2f playerPos = owner->GetScene()->GetGameObject(1)->GetPosition();
		sf::Vector2f delta = playerPos - owner->GetPosition();
		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance >= 400)
			return true;
		else
			return false;
		};
	DestroyState* destroy = new DestroyState();
	destroy->condition = [](GameObject* owner, State* currentState) {return false; };

	Disable* disable = new Disable();
	disable->condition = [](GameObject* owner, State* currentState) {
		Disable* disable = static_cast<Disable*>(currentState);
		Camera* camera = disable->player->GetComponent<Camera>();
		sf::FloatRect rect(owner->GetPosition() - sf::Vector2f(35.f, 35.f), { 70,70 });
		sf::FloatRect view(camera->view.getCenter() - camera->view.getSize() / 2.f, camera->view.getSize());
		if (view.findIntersection(rect))
			return true;
		else
			return false;
		};
	fsm->AddState(disable, patrol);
	fsm->AddState(patrol, chase);
	fsm->AddState(chase, patrol);
	fsm->AddState(destroy, destroy);
	fsm->Init(disable);
}

TopDown::EnemySniper::EnemySniper(RessourceModule* ressourceModule, sf::Vector2f hideSpot, sf::Vector2f snipeSpot) : Enemy(ressourceModule->GetTexture("TopDownBarrelBlue"), ressourceModule->GetTexture("TopDownFrameBlue"))
{
	CreateComponent<EnemySniperAi>();
	EnemyCollision* box = CreateComponent<EnemyCollision>();
	box->Init({ 40, 40 });

	FSM* fsm = CreateComponent<FSM>();
	Hide* hide = new Hide(hideSpot, 10);
	hide->condition = [](GameObject* owner, State* currentState) {
		Hide* hide = static_cast<Hide*>(currentState);
		return hide->hideTimer <= 0;
		};
	Snipe* snipe = new Snipe(snipeSpot, 12);
	snipe->condition = [](GameObject* owner, State* currentState) {
		Snipe* snipe = static_cast<Snipe*>(currentState);
		return snipe->shootDelay <= 0;
		};
	DestroyState* destroy = new DestroyState();
	destroy->condition = [](GameObject* owner, State* currentState) {return false; };
	Disable* disable = new Disable();
	disable->condition = [](GameObject* owner, State* currentState) {
		Disable* disable = static_cast<Disable*>(currentState);
		Camera* camera = disable->player->GetComponent<Camera>();
		sf::FloatRect rect(owner->GetPosition() - sf::Vector2f(35.f,35.f), {70,70});
		sf::FloatRect view(camera->view.getCenter() - camera->view.getSize() / 2.f, camera->view.getSize());
		if (view.findIntersection(rect))
			return true;
		else
			return false;
		};
	fsm->AddState(disable, snipe);
	fsm->AddState(hide, snipe);
	fsm->AddState(snipe, hide);
	fsm->AddState(destroy, destroy);
	fsm->Init(disable);


}

void TopDown::FSM::AddState(State* state, State* nextState)
{
	states[state] = nextState;
}
void TopDown::FSM::Init(State* startState)
{
	currentState = startState;
}

void TopDown::FSM::Start()
{
	for (auto state : states) {
		state.first->owner = static_cast<Enemy*>(owner);
	}
	currentState->Start();
}

void TopDown::FSM::Update(TimeModule* timeModule)
{
	currentState->Update(timeModule);
	if (currentState->ChangeState()) {
		currentState->End();
		for (auto state : states) {
			if (state.first == currentState) {
				currentState = state.second;
				break;
			}
		}
		currentState->Start();
	}

}

void TopDown::FSM::Destroy()
{
	for (auto state : states) {
		delete state.first;
	}
}

bool TopDown::State::ChangeState()
{
	return condition(owner, this);
}

TopDown::Patrol::Patrol(std::vector<sf::Vector2f> _targets): targets(_targets)
{
}

void TopDown::Patrol::Update(TimeModule* timeModule)
{
	if (owner->GetPosition() == targets[currentTarget])
		currentTarget = (currentTarget + 1) % targets.size();
}

void TopDown::Patrol::Start()
{
	std::cout << "Patrol Start" << std::endl;
}

void TopDown::Patrol::End()
{
	std::cout << "Patrol End" << std::endl;
}

void TopDown::EnemyBaseAi::Start()
{
	enemy = static_cast<Enemy*>(owner);
}

void TopDown::EnemyBaseAi::Update(TimeModule* timeModule)
{
	FSM* fsm = owner->GetComponent<FSM>();
	
	if (Patrol* state = dynamic_cast<Patrol*>(fsm->currentState)) {
		enemy->MoveForward(state->targets[state->currentTarget], enemy->speed * timeModule->GetDeltaTime(), false);
		enemy->RotateBarrel(state->targets[state->currentTarget], enemy->rotationBarrelSpeed * timeModule->GetDeltaTime());
	}
	else if (Chase* state = dynamic_cast<Chase*>(fsm->currentState)) {
		enemy->MoveForward(state->target, enemy->speed * timeModule->GetDeltaTime(), true);
		enemy->RotateBarrel(enemy->GetScene()->GetGameObject(1)->GetPosition(), enemy->rotationBarrelSpeed * timeModule->GetDeltaTime());
		enemy->reloadTime -= timeModule->GetDeltaTime();
		if (enemy->reloadTime <= 0) {
			enemy->reloadTime = enemy->reloadTimeMax;
			RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
			enemy->Shoot(ressourceModule->GetTexture("TopDownBulletRed"));
		}
	}
	else if (DestroyState* state = dynamic_cast<DestroyState*>(fsm->currentState)) {
		if (state->smokeTimer <= 0) {
			state->smokeTimer = state->smokeTimerMax;
			Smoke* smoke = new Smoke();
			smoke->SetPosition(owner->GetPosition());
			smoke->SetScale(0.5, 0.5);
			owner->GetScene()->AddGameObject(smoke, 1);
		}
	}
	sf::Vector2f pos = owner->GetPosition();
	pos.x = std::clamp(pos.x, 0.f, 800.f);
	owner->SetPosition(pos);
}
void TopDown::EnemySniperAi::Start()
{
	enemy = static_cast<EnemySniper*>(owner);
}
void TopDown::EnemySniperAi::Update(TimeModule* timeModule)
{
	FSM* fsm = enemy->GetComponent<FSM>();
	if (Hide* state = dynamic_cast<Hide*>(fsm->currentState)) {
		enemy->MoveForward(state->hideSpot, enemy->speed * timeModule->GetDeltaTime(), false);
	}
	else if (Snipe* state = dynamic_cast<Snipe*>(fsm->currentState)) {
		enemy->MoveForward(state->snipeSpot, enemy->speed * timeModule->GetDeltaTime(), false);
		enemy->RotateBarrel(enemy->GetScene()->GetGameObject(1)->GetPosition(),enemy->rotationBarrelSpeed * timeModule->GetDeltaTime());
		if (state->shootDelay <= 3 && state->shooted == false) {
			state->shooted = true;
			RessourceModule* ressourceModule = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
			enemy->Shoot(ressourceModule->GetTexture("TopDownBulletBlue"));
		}
	}
	else if (DestroyState* state = dynamic_cast<DestroyState*>(fsm->currentState)) {
		if (state->smokeTimer <= 0) {
			state->smokeTimer = state->smokeTimerMax;
			Smoke* smoke = new Smoke();
			smoke->SetPosition(owner->GetPosition());
			smoke->SetScale(0.5, 0.5);
			owner->GetScene()->AddGameObject(smoke, 1);
		}
	}
}
void TopDown::Enemy::MoveForward(sf::Vector2f target, float speed, bool rotate) {
	sf::Vector2f delta = target - GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance != 0)
	{
		sf::Vector2f direction = delta / distance;
		float angle = atan2(direction.y, direction.x) * 180 / 3.141;
		float angleDiff = GetRotation() - angle;
		while (angleDiff >= 180 || angleDiff < -180) {
			if (angleDiff < -180)
				angleDiff += 360;
			if (angleDiff >= 180)
				angleDiff -= 360;
		}

		if (abs(angleDiff) <= speed)
			SetRotation(angle);
		else {
			if (angleDiff < 0)
				Rotate(speed);
			else
				Rotate(-speed);

		}
		if(angleDiff == 0 || rotate)
		{
			float ownerAngle = GetRotation() * 3.141 / 180;
			direction = { cos(ownerAngle), sin(ownerAngle) };
			if (distance > speed)
				Move(direction * speed);
			else
				SetPosition(target);
		}
	}
}
void TopDown::Enemy::RotateBarrel(sf::Vector2f target, float speedRotation) {
	sf::Vector2f delta = target - GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance != 0)
	{
		sf::Vector2f direction = delta / distance;
		float angle = atan2(direction.y, direction.x) * 180 / 3.141;
		float rotation = rotationBarrel + GetRotation();
		float angleDiff = rotation - angle;
		while (angleDiff >= 180 || angleDiff < -180) {
			if (angleDiff < -180)
				angleDiff += 360;
			if (angleDiff >= 180)
				angleDiff -= 360;
		}

		if (abs(angleDiff) <= speedRotation)
			rotationBarrel = angle - GetRotation();
		else {
			if (angleDiff < 0)
				rotationBarrel += speedRotation;
			else
				rotationBarrel -= speedRotation;

		}
	}
}
void TopDown::Enemy::Shoot(sf::Texture* tex) {
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	Projectile* projectile = new Projectile(tex, this);
	projectile->SetPosition(GetPosition());
	projectile->SetRotation(GetRotation() + rotationBarrel + rand() % 40 - 20);
	GetScene()->AddGameObject(projectile, GetCalque());
}

void TopDown::Chase::Start()
{
	scene = Engine::GetInstance()->GetModuleManager()->GetModule<SceneModule>()->GetMainScene();
	std::cout << "Chase Start" << std::endl;
}

void TopDown::Chase::Update(TimeModule* timeModule)
{
	std::vector< std::vector<GameObject*>> gameObjects = scene->GetGameObjects();
	directions.clear();
	target = owner->GetPosition();
	for (auto layer : gameObjects) {
		for (auto object : layer) {
			if (object->GetId() == 1) {
				sf::Vector2f delta = object->GetPosition() - owner->GetPosition();
				float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
				if (distance >= 200)
					directions.push_back(delta/distance);
				else
					directions.push_back(-delta / distance);
			}
			else if (object->GetId() == 2) {
				sf::Vector2f delta = object->GetPosition() - owner->GetPosition();
				float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
				if (distance < 150 && distance != 0)
					directions.push_back(-delta / distance);
			}
		}
	}
	for (auto direction : directions) {
		target += direction;
	}
}

void TopDown::Chase::End()
{
	std::cout << "Chase End" << std::endl;
}

void TopDown::EnemyCollision::Collide(CollisionBox* other)
{
	if (other->owner->GetId() == 3) {
		Projectile* projectile = static_cast<Projectile*>(other->owner);
		if (projectile->owner != owner) {
			//std::cout << "target : " << owner->GetId() << " destroy" << std::endl;
			FSM* fsm = owner->GetComponent<FSM>();
			fsm->currentState = fsm->GetState<DestroyState>();
			fsm->currentState->Start();
			projectile->GetScene()->DestroyObject(projectile);
		}
	}
}

void TopDown::DestroyState::Start()
{
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	TankRender* tankRender = owner->GetComponent<TankRender>();
	tankRender->barrel->tex = ressource->GetTexture("TopDownDestroyBarrel");
	tankRender->barrel->sprite.setTexture(*tankRender->barrel->tex, true);
	tankRender->frame->tex = ressource->GetTexture("TopDownDestroyFrame");
	tankRender->frame->sprite.setTexture(*tankRender->frame->tex, true);

}

void TopDown::DestroyState::Update(TimeModule* timeModule)
{
	smokeTimer -= timeModule->GetDeltaTime();
}

TopDown::Hide::Hide(sf::Vector2f _hideSpot, float time):hideSpot(_hideSpot), hideTimerMax(time)
{
}

void TopDown::Hide::Start()
{
	std::cout << "Hide : Start";
	hideTimer = hideTimerMax;
}

void TopDown::Hide::Update(TimeModule* timeModule)
{
	hideTimer -= timeModule->GetDeltaTime();
}

void TopDown::Hide::End()
{
	std::cout << "Hide : End";
}

TopDown::Snipe::Snipe(sf::Vector2f _snipeSpot, float time):snipeSpot(_snipeSpot), shootDelayMax(time)
{
}

void TopDown::Snipe::Start()
{
	shootDelay = shootDelayMax;
	shooted = false;
}

void TopDown::Snipe::Update(TimeModule* timeModule)
{
	shootDelay -= timeModule->GetDeltaTime();
}

void TopDown::Disable::Start()
{
	player = owner->GetScene()->GetGameObject(1);
}

