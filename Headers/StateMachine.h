#pragma once
#include "GameContext.h"
#include "I_State.h"
#include<memory>

class StateMachine
{
public:
	void Start();
	void Tick(gameContext& ctx);
	bool IsRunning() const;

private:
	static std::unique_ptr<IState> CreateState(StateID stateID);//a static factory method to create state objects based on state.
	std::unique_ptr<IState> currentState;
	bool isRunning = false;


};