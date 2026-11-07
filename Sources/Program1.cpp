#include <iostream>
#include "WorldInput.h"
#include "StateMachine.h"

int main()
{
    gameContext game_context;
    WorldInput worldInput;
    StateMachine stateMachine;
    stateMachine.Start();
    while (stateMachine.IsRunning())
    {
        worldInput.UpdateInput(game_context);
        stateMachine.Tick(game_context);

    }
    std::cout << "---THE END---" << std::endl;
    return 0;
}
