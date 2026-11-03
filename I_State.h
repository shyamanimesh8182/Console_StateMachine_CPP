#pragma once
#include "StateHolder.h"
class IState 
{
public:
	virtual ~IState() = default;//important for creating interfaces in c++."ITS A VIRTUAL DESTRUCTOR"
	virtual void Enter() {}//on state enter.
	virtual StateID Update() = 0;//return the next state or the current state.
	virtual void Exit() {}//on state exit.

};