#pragma once
#include "I_State.h"
#include "GameContext.h"
//This header file defines what happens in each state and how the transitions occur between them.

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
		if (ctx.isTargetVisible && ctx.orderReceived)//switches to follow when target found and order received.
		{
			std::cout << "Target found and order received, switching to FOLLOW." << std::endl;
			return StateID::Follow;
		}
		if (ctx.isTargetVisible)//switches to attack when only one target is visible and no order received.
		{
			std::cout << "Target found but no order received, switching to ATTACK." << std::endl;
			return StateID::Attack;
		}
		if (ctx.quitRequested)//switches to quit when quit is requested.
		{
			std::cout << "Quit requested, switching to QUIT, mission aborted." << std::endl;
			return StateID::Quit;
		}

		return StateID::Idle;

	}
	void Exit() override
	{
		//std::cout << "Exiting IDLE state." << std::endl;

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
		if (!ctx.isTargetVisible && !ctx.orderReceived)//switches to idle when target is not found and no order received.
		{
			std::cout << "Target lost and no order received, switching to IDLE." << std::endl;
			return StateID::Idle;
		}
		if (ctx.isTargetVisible && (!ctx.orderReceived || ctx.clearShotAvailable))//switches to attack under the conditions.
		{
			if (!ctx.orderReceived)
				std::cout << "Target in sight and no orders, aiming for a clear shot." << std::endl;
			else
				std::cout << "Target in sight with a clear shot, preparing for attack." << std::endl;
			return StateID::Attack;
		}
		if (ctx.quitRequested)//switches to quit when quit is requested.
		{
			std::cout << "Quit requested, switching to QUIT, mission aborted." << std::endl;
			return StateID::Quit;
		}
		
		return StateID::Follow;

	}
	void Exit() override
	{
		//std::cout << "Exiting FOLLOW state." << std::endl;

	}
	StateID GetStateID() const override
	{
		return StateID::Follow;
	}

};

//ATTACK State
class ATTACK : public IState
{
	//this class defines what happens in attack state.
public:

	void Enter() override
	{
		std::cout << "Target acquired, found a clear shot, switching to ATTACK." << std::endl;

	}
	StateID Update(gameContext& ctx) override
	{
		std::cout << "Ready to engage the target." << std::endl;
		if (ctx.isTargetDead && ctx.orderReceived)// dead target ends the engagement, so it is checked first
		{
			std::cout << "Target eliminated. Mission accomplished." << std::endl;
			return StateID::Quit;
		}
		if (ctx.isTargetDead && !ctx.orderReceived)//switches to idle when target is dead and no order received.
		{
			std::cout << "Target eliminated and no order, switching to IDLE." << std::endl;
			return StateID::Idle;
		}
		if (!ctx.isTargetVisible && !ctx.orderReceived)//switches to idle when target is lost and no order received.
		{
			std::cout << "Target lost and no order, switching to IDLE." << std::endl;
			return StateID::Idle;
		}
		if (!ctx.isTargetVisible && ctx.orderReceived)//switches to follow when target is lost but order is still active.
		{
			std::cout << "Target lost but order active, switching to FOLLOW." << std::endl;
			return StateID::Follow;
		}
		if (ctx.orderReceived && !ctx.clearShotAvailable)//switches to follow when order is received but no clear shot is available.
		{
			std::cout << "No clear shot, repositioning, switching to FOLLOW." << std::endl;
			return StateID::Follow;
		}
		if (ctx.quitRequested)//switches to quit when quit is requested.
		{
			std::cout << "Quit requested, switching to QUIT, mission aborted." << std::endl;
			return StateID::Quit;
		}

		return StateID::Attack;

	}
	void Exit() override
	{
		//std::cout << "Exiting ATTACK state." << std::endl;

	}
	StateID GetStateID() const override
	{
		return StateID::Attack;
	}

};

//QUIT state
class QUIT : public IState
{
	//this states handles the mission ending.
public:
	void Enter() override
	{
		std::cout << "Mission Ending" << std::endl;

	}
	StateID Update(gameContext& ctx) override
	{
		std::cout << "Mission has ended : ";
		//checking for the reason of why the mission has ended.
		if (ctx.isTargetDead)
		{
			std::cout << "Mission Accomplished." << std::endl;
		}
		else if (ctx.missionFailed)
		{
			std::cout << "Mission Failed." << std::endl;
		}
		else if (ctx.quitRequested)
		{
			std::cout << "Mission Aborted." << std::endl;
		}
		else
		{
			std::cout << "Mission Ended for some unknown reason." << std::endl;
		}

		return StateID::Quit;
	}
	void Exit() override 
	{
		std::cout<< "Mission is over, Cya later." << std::endl;

	}
	StateID GetStateID() const override
	{
		return StateID::Quit;
	}

};