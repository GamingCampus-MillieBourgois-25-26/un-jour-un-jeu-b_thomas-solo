#pragma once
#include "GameObject.h"
#include "Component.h"
#include <map>
#include <functional>
#include "Include/Top-Down/TopDown.h"
#include <RessourceModule.h>
#include <CollisionBox.h>
#include "PlayerTopDown.h"


namespace TopDown
{
	class Enemy : public Tank
	{
	public:
		Enemy(sf::Texture* texBarrel, sf::Texture* texFrame);
		void MoveForward(sf::Vector2f target, float speed, bool rotate);
		void RotateBarrel(sf::Vector2f target, float speedRotation);
		void Shoot(sf::Texture* tex);
	};
	class EnemyBase : public Enemy {
	public:
		EnemyBase(RessourceModule* ressourceModule, std::vector<sf::Vector2f>patrolPoints);
	};
	class EnemySniper : public Enemy {
	public:
		EnemySniper(RessourceModule* ressourceModule, sf::Vector2f hideSpot, sf::Vector2f snipeSpot);
	};
	class EnemySniperAi : public Component {
	public:
		Enemy* enemy = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class State {
	public:
		std::function<bool(GameObject* owner, State* currentState)>condition;
		Enemy* owner;
		bool ChangeState();
		virtual void Start() {};
		virtual void Update(TimeModule* timeModule) {};
		virtual void End() {};
	};
	class EnemyBaseAi : public Component {
	public:
		Enemy* enemy = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class EnemyCollision : public CollisionBox {
	public:
		void Collide(CollisionBox* other)override;
	};
	class FSM : public Component {
	public:
		std::map<State*, State*>states;
		State* currentState;
		void AddState(State* state, State* nextState);
		template<typename StateType>
		StateType* GetState();
		void Init(State* startState);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Destroy()override;
	};
	class Patrol : public State
	{
	public:
		std::vector<sf::Vector2f> targets;
		int currentTarget = 0;
		Patrol(std::vector<sf::Vector2f> _targets);
		void Update(TimeModule* timeModule)override;
		void Start()override;
		void End()override;
	};

	class Chase : public State 
	{
	public:
		std::vector<sf::Vector2f> directions;
		sf::Vector2f target;
		Scene* scene = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void End()override;
	};
	class DestroyState : public State
	{
	public:
		float smokeTimer = 0;
		float smokeTimerMax = 1.3;
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class Hide : public State
	{
	public:
		float hideTimer = 5;
		float hideTimerMax = 5;
		sf::Vector2f hideSpot;
		Hide(sf::Vector2f _hideSpot, float time);
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void End()override;
	};
	class Snipe : public State
	{
	public:
		float shootDelay = 5;
		float shootDelayMax = 5;
		bool shooted = false;
		sf::Vector2f snipeSpot;
		Snipe(sf::Vector2f _snipeSpot, float time);
		void Start()override;
		void Update(TimeModule* timeModule)override;
	};
	class Disable : public State
	{
	public:
		GameObject* player = nullptr;
		void Start()override;
	};
	

}
#include"EnemyTopDown.inl"

