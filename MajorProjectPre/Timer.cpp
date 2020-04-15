#include "Timer.h"


#pragma region Constructors

Timer::Timer(std::string owner) 
	: start(std::chrono::high_resolution_clock::now()), end(), duration(), owner(owner) {}

Timer::~Timer()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;

	if (owner == "")
	{
		float milliseconds = duration.count() * 1000.0f;
		std::cout << milliseconds << "ms" << std::endl;
	}
	else
	{
		float milliseconds = duration.count() * 1000.0f;
		std::cout << owner << " took - " << milliseconds << "ms" << " to run" << std::endl;
	}

}

#pragma endregion

#pragma region Properties

float Timer::GetTime()
{
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;

	return duration.count() * 1000.0f;
}

#pragma endregion
