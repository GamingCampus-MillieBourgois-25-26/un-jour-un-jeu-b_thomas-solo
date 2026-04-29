#pragma once
#include "GameObject.h"
#include "Component.h"
#include <map>
#include <functional>
namespace TopDown
{
	class Enemy : public GameObject
	{
	public:
		Enemy();
	};
	class State {
	public:
		std::function<bool()>condition;
		Enemy* owner;
		bool ChangeState();
		virtual void Start() {};
		virtual void Update(TimeModule* timeModule) {};
		virtual void End() {};
	};
	class EnemyMovement : public Component {
	public:
		void Update(TimeModule* timeModule)override;
		void Move(sf::Vector2f target, float speed);
	};
	class FSM : public Component {
	public:
		std::map<State*, State*>states;
		State* currentState;
		void AddState(State* state, State* nextState);
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
	};
	
}

