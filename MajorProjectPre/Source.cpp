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
#define VIVABMP "C:\\GitHub\\MajorProject\\MajorProjectPre\\vivaBMP.bmp"

// Text
#define VIVA "C:\\GitHub\\MajorProject\\MajorProjectPre\\viva.txt"

#pragma endregion

#pragma endregion

int main()
{
	// CREATE A NEW BMP
	BMPWriter imageCreator;

	imageCreator.CreateNewBMP("vivaBMP.bmp", 32, 32, RGB(255, 0, 0));

	


	// READ THE MESSAGE AND IMAGE
	FileReader message(VIVA);

	FileReader coverImage(VIVABMP);




	// EMBED THE IMAGE AND PROVIDE FILENAME
	Stego stegoImage(&coverImage, &message, "vivaStegoImage.bmp");

	



	// LOAD NEW IMAGE FROM DIRECTORY AND SAVE INTO BMP OBJECT
	FileReader stegoLoader(stegoImage.GetStegoFileName());

	BMP newBMPVIVA(&stegoLoader);





	// PRINT NEW IMAGES PIXEL VALUES
	newBMPVIVA.PrintPixels();

	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);