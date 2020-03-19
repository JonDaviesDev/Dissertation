#pragma region Preprocessor Directives

#pragma region Includes

#include "BMP.h"
#include "FileLoader.h"
#include "BMPWriter.h"
#include "Stego.h"
#include "JPEGio.h"
#include "JPEG.h"
#include "Decoder.h"
#include "Menu.h"

#pragma endregion


#pragma endregion

int main()
{
	Menu menu;

	// NEED TO FIGURE OUT A WAY OF SENDING OVER THE NUMBER OF PIXELS TO DECODE



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