#include<iostream>
#include<string>
#include"WorldInput.h"
#include"GameContext.h"
#include <algorithm>
#include<cctype>

//a small helper function returns true or false based on our input.
static bool AskQ(const std::string Q)
{
	std::cout << Q << " (y/n):";
	std::string input;
	std::getline(std::cin, input);
	if (input.empty()) return false;
	if (input[0] == 'y' || input[0] == 'Y') return true;
	else return false;

}

// a small helper to convert flags to yes/no.
static const char* BoolToStr(bool b)
{
	return b ? "Yes" : "No";
}

//this function updates the game context based on user input.
void WorldInput::UpdateInput(gameContext& ctx)
{
	//current situation of the game context.
	std::cout << "Target Visible : " << BoolToStr(ctx.isTargetVisible) << std::endl;
	std::cout << "Order Received : " << BoolToStr(ctx.orderReceived) << std::endl;
	std::cout << "Clear Shot on Target : " << BoolToStr(ctx.clearShotAvailable) << std::endl;
	std::cout << "Target Dead : " << BoolToStr(ctx.isTargetDead) << std::endl;
	std::cout << "Quit Requested : " << BoolToStr(ctx.quitRequested) << std::endl;
	std::cout << "Mission Failed : " << BoolToStr(ctx.missionFailed) << std::endl;

	// the turn menu, turn passes, nothing changes.
	//here we get know about the mission details.
	std::cout << "Enter = pass turn | C = change conditions | Q = quit | F = mission failed" << std::endl;
	std::string choice;
	//std::getline(std::cin, choice);
	//if read failed, quit requested is true.
	if (!std::getline(std::cin, choice))
	{
		ctx.quitRequested = true;
		return;
	}
	if (choice.empty()) return;
	char letter = static_cast<char>(std::tolower(choice[0]));
	if (letter == 'q')
	{
		ctx.quitRequested = true;
		return;
	}
	if (letter == 'f')
	{
		ctx.missionFailed = true;
		return;
	}
	if (letter != 'c')
	{
		std::cout << "Unknown Command." << std::endl;
		return;
	}

	//asking questions
	//in this part we get to know about the target and order details.
	if (!ctx.isTargetDead)
	{
		ctx.isTargetDead = AskQ("Is the target DEAD?");
	}
	if (ctx.isTargetDead)
	{
		ctx.isTargetVisible = false;
		ctx.clearShotAvailable = false;
	}
	else
	{
		ctx.isTargetVisible = AskQ("IS the target visible?");
		if (ctx.isTargetVisible)
			ctx.clearShotAvailable = AskQ("Is there a clear shot on the target?");
		else
			ctx.clearShotAvailable = false;
	}
	ctx.orderReceived = AskQ("Is the order received?");

}