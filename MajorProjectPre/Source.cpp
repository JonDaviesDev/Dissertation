#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileReader.h"
#include "BMPWriter.h"
#include "Stego.h"

#pragma endregion

#pragma region Defines

// Images
#define STRIPESPATH "C:\\GitHub\\MajorProject\\ImageSamples\\stripes.bmp"
#define TESTPATH "C:\\GitHub\\MajorProject\\MajorProjectPre\\test.bmp"
#define LENAPATH "C:\\GitHub\\MajorProject\\ImageSamples\\lena.bmp"
#define REDSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\RedSquare.bmp"
#define GREENSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\GreenSquare.bmp"
#define BITWISETEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\bitTest.bmp"

// Text
#define TEXT "C:\\GitHub\\MajorProject\\MajorProjectPre\\hello.txt"

#pragma endregion

#pragma endregion

int main()
{
	FileReader image("C:\\GitHub\\MajorProject\\MajorProjectPre\\LSBtest2.bmp");

	BMP bmp(&image);

	BMPWriter w;

	w.CloneBMP(&bmp, "copyTest.bmp");
	
	//FileReader image(REDSQUARE);

	//FileReader text(TEXT);

	//Stego st(&image, &text);

	return 0;
}
