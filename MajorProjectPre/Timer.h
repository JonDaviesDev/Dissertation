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
	Timer(std:: string owner = "");
	~Timer();

#pragma endregion

#pragma region Properties

	float GetTime();

#pragma endregion


};

