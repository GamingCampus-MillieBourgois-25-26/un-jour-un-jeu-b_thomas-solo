#include <Include/Top-Down/EnemyTopDown.h>
#include <Include/BasicBox.h>

TopDown::Enemy::Enemy()
{
	CreateComponent<BasicBox>(20,20);
	CreateComponent<EnemyMovement>();

	FSM* fsm = CreateComponent<FSM>();
	std::vector<sf::Vector2f> target({ sf::Vector2f(100.f, 100.f), sf::Vector2f(300.f, 300.f) });
	Patrol* patrol = new Patrol(target);
	patrol->condition = []() {return false; };
	fsm->AddState(patrol, patrol);
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
	return condition();
}

TopDown::Patrol::Patrol(std::vector<sf::Vector2f> _targets): targets(_targets)
{
}

void TopDown::Patrol::Update(TimeModule* timeModule)
{
	if (owner->GetPosition() == targets[currentTarget])
		currentTarget = (currentTarget + 1) % targets.size();
}

void TopDown::EnemyMovement::Update(TimeModule* timeModule)
{
	FSM* fsm = owner->GetComponent<FSM>();
	Patrol* state = dynamic_cast<Patrol*>(fsm->currentState);
	if (state) {
		Move(state->targets[state->currentTarget], 30 * timeModule->GetDeltaTime());
	}
}
void TopDown::EnemyMovement::Move(sf::Vector2f target, float speed) {
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
		if(angleDiff == 0 )
		{
			if (distance <= speed)
				owner->SetPosition(target);
			else
			{
				sf::Vector2f direction = delta / distance;
				owner->Move(direction * speed);
			}
		}
	}
}
