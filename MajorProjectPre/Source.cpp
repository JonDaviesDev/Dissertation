#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileReader.h"

#pragma endregion

#pragma region Defines

#define FILEPATH "C:\\Users\\jonny\\source\\repos\\MajorProject\\MajorProjectPre\\ImageSamples\\stripes.BMP"

#pragma endregion

#pragma endregion


int main()
{
	FileReader reader(FILEPATH);

	// Dependencies in BMPInfoHeader and BMPFIleHeader - both rely on each other before they can be created.
	// Decouple them?

	BMP bmp(&reader);

	return 0;
}


/*const char* fileName = {FILEPATH};

	BMP* myBMP = new BMP();

	myBMP->ScanBMP(fileName, "rb");

	myBMP->Write(fileName);*/