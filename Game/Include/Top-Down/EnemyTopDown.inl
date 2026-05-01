#pragma once
template<typename StateType>
inline StateType* TopDown::FSM::GetState()
{
	for (auto state : states) {
		StateType* res = dynamic_cast<StateType*>(state.first);
		if (res) {
			return res;
		}
	}
	return nullptr;
}