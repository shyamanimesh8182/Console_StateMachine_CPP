#pragma once
#include "StateHolder.h"
#include "GameContext.h"

class IState 
{
public:
	virtual ~IState() = default;//important for creating interfaces in c++."ITS A VIRTUAL DESTRUCTOR"
	virtual void Enter() = 0;//on state enter.
	virtual StateID Update(gameContext& ctx) = 0;//return the next state or stay in the current state.
	virtual void Exit() = 0;//on state exit.
	virtual StateID GetStateID() const = 0;
};