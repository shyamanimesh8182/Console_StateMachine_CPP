#include "StateMachine.h"
#include "States.h"
#include "GameContext.h"
#include<memory>

//using the factory method to create state objects based on state using switch-case block.
std::unique_ptr<IState> StateMachine::CreateState(StateID stateID)
{
	switch (stateID)
	{
	case StateID::Idle:
		return std::make_unique<IDLE>();
	case StateID::Follow:
		return std::make_unique<FOLLOW>();
	case StateID::Attack:
		return std::make_unique<ATTACK>();
	case StateID::Quit:
		return std::make_unique<QUIT>();

	default:
		return nullptr;
	}

}

//If state is idle, enter and start running. 
void StateMachine::Start()
{
	currentState = CreateState(StateID::Idle);
	if (currentState != nullptr)
	{
		currentState->Enter();
		isRunning = true;
	}
	else
	{
		std::cerr << "Failed to create initial state." << std::endl;
		isRunning = false;
	}

}

//returns whetheer the machine is running or not.
bool StateMachine::IsRunning() const
{
	return isRunning;
}

// a small helper function which converts the stateID into string for debugging purpose.
static const char* StateIdString(StateID id)
{
	switch (id)
	{
	case StateID::Idle:
		return "Idle";
	case StateID::Follow:
		return "Follow";
	case StateID::Attack:
		return "Attack";
	case StateID::Quit:
		return "Quit";

	default:
		return "Unknown State";
	}

}

//the most important method, It runs every frame 
//It operates the statemachine.
//It handles the transition between states by calling exit and enter methods of the states.
void StateMachine::Tick(gameContext& ctx)
{

	if (!isRunning) return;
	StateID currentID = currentState->GetStateID();
	StateID nextID;
	if (ctx.quitRequested || ctx.missionFailed)
	{
		nextID = StateID::Quit;
		//when the mission is failed or quit is requested, switched to quit state.
	}
	else
	{
		nextID = currentState->Update(ctx);

	}
	if (nextID != currentID)
	{
		currentState->Exit();//exiting the current state.
		std::cout << "Exiting the " << StateIdString(currentState->GetStateID()) << " state." << std::endl;
		currentState = CreateState(nextID);//creating the next state.
		currentState->Enter();//entering the new state.
		std::cout << "Entering the " << StateIdString(currentState->GetStateID()) << " state." << std::endl;

	}
	if (currentState->GetStateID() == StateID::Quit)
	{
		currentState->Update(ctx);//updating to check reason for mission ending.
		isRunning = false;

	}

}