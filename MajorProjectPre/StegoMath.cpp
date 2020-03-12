#include "StegoMath.h"


#pragma region Constructors

StegoMath::StegoMath() {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

float StegoMath::FindLength(RGB pixel)
{
	return sqrt((pixel.GetRed() * pixel.GetRed()) + (pixel.GetGreen() * pixel.GetGreen()) + (pixel.GetBlue() * pixel.GetBlue()));
}

int StegoMath::RoundToInt(float value)
{
	return (int)roundf(value);
}

int StegoMath::FindModulus(int distance, int modValue)
{
	return distance % modValue;
}

int StegoMath::DetermineSegment(int remainder, int modValue)
{
	// Basic error checking - Make sure that the value does not fall out of the allowed range
	if(remainder < 0 || remainder > modValue)
	{
		if(remainder < 0)
		{
			std::cout << "STEGO::DETERMINESEGEMENT::VALUE_CANNOT_BE_LESS_THAN_ZERO" << std::endl;
		}

		if(remainder > modValue)
		{
			std::cout << "STEGO::DETERMINESEGEMENT::VALUE_CANNOT_BE_GREATER_THAN_MODULUS_VALUE" << std::endl;
		}

		exit(-1);
	}

	if(remainder >= 0 && remainder <= (modValue / 2))
	{
		return 0;
	}
	else return 1;

}

#pragma endregion