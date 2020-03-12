#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileLoader.h"
#include "BMPWriter.h"
#include "Stego.h"
#include "JPEGReader.h"
#include "JPEG.h"
#include "Decoder.h"

#pragma endregion

#pragma region Defines

// Images - BMP
#define STRIPESPATH "C:\\GitHub\\MajorProject\\ImageSamples\\stripes.bmp"
#define TESTPATH "C:\\GitHub\\MajorProject\\MajorProjectPre\\DTOTest.bmp"
#define LENAPATH "C:\\GitHub\\MajorProject\\ImageSamples\\lena.bmp"
#define REDSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\RedSquare.bmp"
#define GREENSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\GreenSquare.bmp"
#define BITWISETEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\bitTest.bmp"
#define LSBTEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\LSBtest2.bmp"
#define VIVABMP "C:\\GitHub\\MajorProject\\MajorProjectPre\\vivaBMP.bmp"

// Images - JPEG
#define JPEGTEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\changesDTO.jpg"

// Text
#define VIVA "C:\\GitHub\\MajorProject\\MajorProjectPre\\viva.txt"

#pragma endregion

#pragma endregion

int main()
{
	/*FileLoader jpegLoader(JPEGTEST);

	JPEGReader reader(&jpegLoader);

	JPEG jpeg(&reader);

	jpeg.Print();*/


	//// CREATE A NEW BMP
	//BMPWriter imageCreator;

	//imageCreator.CreateNewBMP("DTOTest.bmp", 32, 32, RGB(182, 232, 76));



	//// READ THE MESSAGE AND IMAGE
	//FileLoader message(VIVA);

	//FileLoader coverImage(TESTPATH);




	//// EMBED THE IMAGE AND PROVIDE FILENAME
	//Stego stegoImage(&coverImage, &message, "changesDTO.bmp");




	// LOAD NEW IMAGE FROM DIRECTORY AND SAVE INTO BMP OBJECT
	FileLoader stegoLoader(JPEGTEST);

	JPEGReader jpr(&stegoLoader);

	JPEG jpg(&jpr);

	//BMP newBMPVIVA(&stegoLoader);

	Decoder d(&jpg);


	// PRINT NEW IMAGES PIXEL VALUES
	//newBMPVIVA.PrintPixels();

	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);