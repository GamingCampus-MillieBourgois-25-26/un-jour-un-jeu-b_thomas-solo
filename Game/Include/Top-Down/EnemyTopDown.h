#pragma once
#include "GameObject.h"
#include "Component.h"
#include <map>
#include <functional>
#include "Include/Top-Down/TopDown.h"
#include <RessourceModule.h>
#include <CollisionBox.h>


namespace TopDown
{
	class Enemy : public Tank
	{
	public:
		Enemy(RessourceModule* ressource);
	};
	class State {
	public:
		std::function<bool(GameObject* owner)>condition;
		Enemy* owner;
		bool ChangeState();
		virtual void Start() {};
		virtual void Update(TimeModule* timeModule) {};
		virtual void End() {};
	};
	class EnemyMovement : public Component {
	public:
		Enemy* enemy = nullptr;
		void Start()override;
		void Update(TimeModule* timeModule)override;
		void Move(sf::Vector2f target, float speed, bool rotate);
		void RotateBarrel(sf::Vector2f target, float speedRotation);
		void Shoot();
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
	
	template<typename StateType>
	inline StateType* FSM::GetState()
	{
		for (auto state : states) {
			StateType* res = dynamic_cast<StateType*>(state.first);
			if (res) {
				return res;
			}
		}
		return nullptr;
	}

}

