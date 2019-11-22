#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileReader.h"
#include "BMPWriter.h"

#pragma endregion

#pragma region Defines

#define STRIPESPATH "C:\\GitHub\\MajorProject\\ImageSamples\\stripes.bmp"
#define TESTPATH "C:\\GitHub\\MajorProject\\MajorProjectPre\\theTest.bmp"

#pragma endregion

#pragma endregion


int main()
{
	FileReader reader(TESTPATH);

	BMP bmp(&reader);

	BMPWriter newBMP;

	newBMP.CreateNewBMP(&bmp);

	//newBMP.CloneBMP(&bmp);

	//newBMP.CreateNewBMP("theTest.bmp", 500, 500, RGB(255, 255, 200));

	return 0;

















	// TODO: go back and open/close in each function
}
