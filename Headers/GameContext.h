#pragma once

//we use this header file for declaring all the conditions that we require in our system.

struct gameContext 
{
	bool isTargetVisible = false;
	bool orderReceived = false;
	bool clearShotAvailable = false;
	bool isTargetDead = false;
	bool quitRequested = false;
	bool missionFailed = false;
};