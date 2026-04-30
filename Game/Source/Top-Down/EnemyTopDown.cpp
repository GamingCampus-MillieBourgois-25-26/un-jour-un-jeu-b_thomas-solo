#include <Include/Top-Down/EnemyTopDown.h>
#include <Engine.h>
#include <SceneModule.h>
#include <Include/BasicBox.h>
#include <Include/Top-Down/ProjectileTopDown.h>
#include "Include/Top-Down/Smoke.h"


TopDown::Enemy::Enemy(RessourceModule* ressource): Tank(ressource->GetTexture("TopDownEnemyBarrel"), ressource->GetTexture("TopDownEnemyFrame"))
{
	speed = 55;
	rotationBarrelSpeed = 40;
	CreateComponent<EnemyMovement>();
	EnemyCollision* box = CreateComponent<EnemyCollision>();
	box->Init({ 40,40 });

	FSM* fsm = CreateComponent<FSM>();
	std::vector<sf::Vector2f> target({ sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 300.f) });
	Patrol* patrol = new Patrol(target);
	patrol->condition = [](GameObject* owner) {
		sf::Vector2f playerPos = owner->GetScene()->GetGameObject(1)->GetPosition();
		sf::Vector2f delta = playerPos - owner->GetPosition();
		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance <= 250)
			return true;
		else
			return false;
		};
	Chase* chase = new Chase();
	chase->condition = [](GameObject* owner) {
		sf::Vector2f playerPos = owner->GetScene()->GetGameObject(1)->GetPosition();
		sf::Vector2f delta = playerPos - owner->GetPosition();
		float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
		if (distance >= 400)
			return true;
		else
			return false;
		};
	DestroyState* destroy = new DestroyState();
	destroy->condition = [](GameObject* owner) {return false; };
	fsm->AddState(patrol, chase);
	fsm->AddState(chase, patrol);
	fsm->AddState(destroy, destroy);
	fsm->Init(patrol);
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
	currentState->Start();
	for (auto state : states) {
		state.first->owner = static_cast<Enemy*>(owner);
	}
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
	return condition(owner);
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

void TopDown::EnemyMovement::Start()
{
	enemy = static_cast<Enemy*>(owner);
}

void TopDown::EnemyMovement::Update(TimeModule* timeModule)
{
	FSM* fsm = owner->GetComponent<FSM>();
	
	if (Patrol* state = dynamic_cast<Patrol*>(fsm->currentState)) {
		Move(state->targets[state->currentTarget], enemy->speed * timeModule->GetDeltaTime(), false);
		RotateBarrel(state->targets[state->currentTarget], enemy->rotationBarrelSpeed * timeModule->GetDeltaTime());
	}
	else if (Chase* state = dynamic_cast<Chase*>(fsm->currentState)) {
		Move(state->target, enemy->speed * timeModule->GetDeltaTime(), true);
		RotateBarrel(enemy->GetScene()->GetGameObject(1)->GetPosition(), enemy->rotationBarrelSpeed);
		enemy->reloadTime -= timeModule->GetDeltaTime();
		if (enemy->reloadTime <= 0) {
			enemy->reloadTime = enemy->reloadTimeMax;
			Shoot();
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
	pos.y = std::clamp(pos.y, 0.f, 800.f);
	owner->SetPosition(pos);
}
void TopDown::EnemyMovement::Move(sf::Vector2f target, float speed, bool rotate) {
	sf::Vector2f delta = target - owner->GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance != 0)
	{
		sf::Vector2f direction = delta / distance;
		float angle = atan2(direction.y, direction.x) * 180 / 3.141;
		float angleDiff = owner->GetRotation() - angle;
		while (angleDiff >= 180 || angleDiff < -180) {
			if (angleDiff < -180)
				angleDiff += 360;
			if (angleDiff >= 180)
				angleDiff -= 360;
		}

		if (abs(angleDiff) <= speed)
			owner->SetRotation(angle);
		else {
			if (angleDiff < 0)
				owner->Rotate(speed);
			else
				owner->Rotate(-speed);

		}
		if(angleDiff == 0 || rotate)
		{
			float ownerAngle = owner->GetRotation() * 3.141 / 180;
			direction = { cos(ownerAngle), sin(ownerAngle) };
			if (distance > speed)
				owner->Move(direction * speed);
			else
				owner->SetPosition(target);
		}
	}
}
void TopDown::EnemyMovement::RotateBarrel(sf::Vector2f target, float speedRotation) {
	sf::Vector2f delta = target - owner->GetPosition();
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
	if (distance != 0)
	{
		sf::Vector2f direction = delta / distance;
		float angle = atan2(direction.y, direction.x) * 180 / 3.141;
		float rotation = enemy->rotationBarrel + owner->GetRotation();
		float angleDiff = rotation - angle;
		while (angleDiff >= 180 || angleDiff < -180) {
			if (angleDiff < -180)
				angleDiff += 360;
			if (angleDiff >= 180)
				angleDiff -= 360;
		}

		if (abs(angleDiff) <= speedRotation)
			enemy->rotationBarrel = angle - owner->GetRotation();
		else {
			if (angleDiff < 0)
				enemy->rotationBarrel += speedRotation;
			else
				enemy->rotationBarrel -= speedRotation;

		}
	}
}
void TopDown::EnemyMovement::Shoot() {
	RessourceModule* ressource = Engine::GetInstance()->GetModuleManager()->GetModule<RessourceModule>();
	Projectile* projectile = new Projectile(ressource->GetTexture("TopDownEnemyBullet"), enemy);
	projectile->SetPosition(owner->GetPosition());
	projectile->SetRotation(owner->GetRotation() + enemy->rotationBarrel + rand() % 40 - 20);
	owner->GetScene()->AddGameObject(projectile, owner->GetCalque());
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
