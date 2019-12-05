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
#define LSBTEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\LSBtest2.bmp"

// Text
#define TEXT "C:\\GitHub\\MajorProject\\MajorProjectPre\\hello.txt"
#define AUSTIN "C:\\GitHub\\MajorProject\\MajorProjectPre\\Austin.txt"

#pragma endregion

#pragma endregion

int main()
{
	// Create stego file
	FileReader image(TESTPATH);

	FileReader text(TEXT);

	Stego st(&image, &text);




	// Read new file to make sure it works
	FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

	BMP newBMP(&newFile);

	return 0;
}
