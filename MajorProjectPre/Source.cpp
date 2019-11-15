#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"

#pragma endregion

#pragma region Defines

#define FILEPATH "C:\\Users\\jonny\\source\\repos\\MajorProject\\MajorProjectPre\\ImageSamples\\stripes.BMP"

#pragma endregion

#pragma endregion


int main()
{
	const char* fileName = {FILEPATH};

	BMP* myBMP = new BMP();

	myBMP->ScanBMP(fileName, "rb");

	myBMP->Write(fileName);

	return 0;
}
