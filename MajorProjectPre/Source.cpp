#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileReader.h"
#include "BMPWriter.h"
#include <array>

#pragma endregion

#pragma region Defines

#define STRIPESPATH "C:\\GitHub\\MajorProject\\ImageSamples\\stripes.bmp"
#define TESTPATH "C:\\GitHub\\MajorProject\\MajorProjectPre\\test.bmp"
#define LENAPATH "C:\\GitHub\\MajorProject\\ImageSamples\\lena.bmp"
#define REDSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\RedSquare.bmp"
#define GREENSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\GreenSquare.bmp"

#pragma endregion

#pragma endregion

int main()
{
	FileReader reader(TESTPATH);

	BMP bmp(&reader);

	BMPWriter newBMP;

	newBMP.CreateNewBMP("newtest.bmp", 500, 500, RGB(99, 255, 255));






	return 0;
}
