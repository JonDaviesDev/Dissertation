#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileLoader.h"
#include "BMPWriter.h"
#include "Stego.h"
#include "JPEGReader.h"
#include "JPEG.h"
#include "Decoder.h"
#include "Menu.h"

#pragma endregion

#pragma region Defines



// Images - BMP
#define STRIPESPATH "C:\\GitHub\\MajorProject\\ImageSamples\\stripes.bmp"
#define TESTPATH "C:\\GitHub\\MajorProject\\ImageSamples\\BMP\\DTOTest.bmp"
#define LENAPATH "C:\\GitHub\\MajorProject\\ImageSamples\\lena.bmp"
#define REDSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\RedSquare.bmp"
#define GREENSQUARE "C:\\GitHub\\MajorProject\\ImageSamples\\GreenSquare.bmp"
#define BITWISETEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\bitTest.bmp"
#define LSBTEST "C:\\GitHub\\MajorProject\\MajorProjectPre\\LSBtest2.bmp"
#define VIVABMP "C:\\GitHub\\MajorProject\\MajorProjectPre\\vivaBMP.bmp"

// Images - JPEG
#define JPEGTEST "C:\\GitHub\\MajorProject\\ImageSamples\\JPEG\\DTOTest1-Converted-Medium.jpg"

// Text
#define VIVA "C:\\GitHub\\MajorProject\\MessageSamples\\viva.txt"

#pragma endregion

#pragma endregion

int main()
{
	Menu menu;


#pragma region LSB Tests

	//const char* imageNameLSB = "LSBTest1-Created.bmp";

	////// CREATE A NEW BMP
	//BMPWriter imageCreator;

	//FileLoader stegoLoader("LSBTest1-Created.bmp");

	//imageCreator.CreateNewBMP(imageNameLSB, 32, 32, RGB(100, 200, 100));



	//// READ THE MESSAGE AND IMAGE
	//FileLoader message(VIVA);

	//FileLoader coverImage(imageNameLSB);



	//// EMBED THE IMAGE AND PROVIDE NEW FILENAME
	//Stego stegoImage(&coverImage, &message, "LSBTest1-Embedded.bmp");

#pragma endregion


#pragma region DTO Tests

	//const char* imageNameDTO = "DTOTest1-Created.bmp";

	////// CREATE A NEW BMP
	//BMPWriter imageCreator;

	//FileLoader stegoLoader("DTOTest1-Created.bmp");

	//imageCreator.CreateNewBMP(imageNameDTO, 32, 32, RGB(100, 200, 100));



	//// READ THE MESSAGE AND IMAGE
	//FileLoader message(VIVA);

	//FileLoader coverImage(imageNameDTO);



	//// EMBED THE IMAGE AND PROVIDE NEW FILENAME
	//Stego stegoImage(&coverImage, &message, "DTOTest1-Embedded.bmp");

#pragma endregion


#pragma region JPEG Creation

	//// LOAD NEW IMAGE FROM DIRECTORY AND SAVE INTO JPEG OBJECT
	//FileLoader stegoLoader(JPEGTEST);

	//JPEGReader jpr(&stegoLoader);

	//JPEG jpg(&jpr);

#pragma endregion



	// Second arguement is a flag to decide on using the DTO (1) or LSB (0) methods
	//Decoder d(&jpg, 1);


	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);