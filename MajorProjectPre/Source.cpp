#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileReader.h"
#include "BMPWriter.h"

#pragma endregion

#pragma region Defines

#define FILEPATH "C:\\Users\\jonny\\source\\repos\\MajorProject\\MajorProjectPre\\ImageSamples\\stripes.BMP"

#pragma endregion

#pragma endregion


int main()
{
	//FileReader reader(FILEPATH);

	//BMP bmp(&reader);

	BMPWriter newBMP;

	newBMP.CreateNewBMP();

	return 0;

	// Replace C++ with C style file loading


	// TODO: go back and open/close in each function
}
