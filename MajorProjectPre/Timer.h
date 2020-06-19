#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Timer
{
#pragma region Attributes

public:
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;
	std::string owner;

#pragma endregion

#pragma region Constructors

public:
	// Start time on construction
	Timer(const std:: string& owner = "");

	// Display time on destruction
	~Timer();

#pragma endregion

#pragma region Properties

	// If the time is needed before destruction
	float GetTime();

#pragma endregion


};

