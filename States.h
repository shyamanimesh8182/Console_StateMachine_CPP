#pragma once
#include "I_State.h"
#include "GameContext.h"

//IDLE State
class IDLE : public IState
{
	//this class defines what happens in idle state.
public:

	void Enter() override
	{
		std::cout << "Starting off with the IDLE state." << std::endl;

	}
	StateID Update(gameContext& ctx	) override
	{
		std::cout << "Sitting stealthy and looking for any potential targets."<<std::endl;
		if (ctx.isTargetVisible && ctx.orderReceived) return StateID::Follow;//switches to follow when target found and order received.
		if (ctx.isTargetVisible) return StateID::Attack;//switches to attack when only one target is visible and no order received.

		return StateID::Idle;

	}
	void Exit() override
	{
		std::cout << "Tango found (or) order received, Switching states to Idle/Follow" << std::endl;

	}
	StateID GetStateID() const override
	{
		return StateID::Idle;
	}

};

// FOLLOW State
class FOLLOW : public IState
{
	//this class defines what happens in follow state.
public:

	void Enter() override
	{
		std::cout << "Command received, switching to FOLLOW." << std::endl;

	}
	StateID Update(gameContext& ctx) override
	{
		std::cout << "Following the target. Position being updated every moment." << std::endl;
		if (!ctx.isTargetVisible && !ctx.orderReceived) return StateID::Idle;//switches to idle when target is not found and no order received.
		if (ctx.isTargetVisible && !ctx.orderReceived) return StateID::Attack;//switches to attack when target insight and no order received.
		if (ctx.isTargetVisible && ctx.clearShotAvailable) return StateID::Attack;//switches to attack when target is found and clear shot available.
		
		return StateID::Follow;

	}
	void Exit() override
	{
		std::cout << "Target lost or order received, switching to IDLE" << std::endl;
		std::cout << "OR" << std::endl;
		std::cout << "Clean shot available, switching to ATTACK" << std::endl;

	}
	StateID GetStateID() const override
	{
		return StateID::Follow;
	}

};

//ATTACK State
class ATTACk : public IState
{

public:



};