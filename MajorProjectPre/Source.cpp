#pragma region Preprocessor Directives

#pragma region Includes

#include <thread>

#include "BMP.h"
#include "FileLoader.h"
#include "BMPWriter.h"
#include "Stego.h"
#include "JPEGio.h"
#include "JPEG.h"
#include "Decoder.h"
#include "Menu.h"
#include "Test.h"
#include "Exporter.h"

#pragma endregion

#pragma endregion


int main()
{

#pragma region Menu

	// README
	/* The menu system will allow you:
	   1. to create BMPs 
	   2. import a bmp from a list of samples or one that you have created
	   3. Embed a message into a bmp (choose from a selction of messages) - please note that the program will exit if
	      the message size is too large for the image.
	   4. Convert the image into a JPEG
	   5. Decode the message out of the JPEG


	   Notes -

	   If you see the main menu after completing an operation, it means that it completed successfully



	   When creating/embedding an image, dimensions of 512x512 work best in relation to creation speed and storage size
	   
	   Check the project directory after creation to see your new image

	   When selecting an image to import, the program will read the contents of both the project directory and a directory in the
	   solution folder called 'ImageSamples', and present you with a list of all of these to choose from.



	   Because the message is being stored in the top line of the image, if you create a BMP with small dimensions, say 32x32,
	   and then try to put a large message inside the program, it will lead to an exception.



	   Lastly, when selecting a JPEG to decode, ensure that you choose the filename that you created but with the '.jpg' extension.

	*/

	Menu menu;

#pragma endregion

#pragma region Automated testing code

	// Uncomment this code to run a series of tests using values of your choosing (please keep 'numberOfCycles' to <=10)


	//Test* tester;
	//Exporter* ex = new Exporter("Mod42.csv"); 

	//int compressionLevel = 10;
	//int numberOfCycles = 10;
	//int testsPerCycle = 5;
	//Method currentMethod = Method::DTO;

	//int modulus = 42;
	
	//int k = 0;
	
	//for (int j = 0; j < numberOfCycles; j++)
	//{
	//	tester = new Test(testsPerCycle, compressionLevel, modulus, currentMethod);
	
	//	ex->AddData(j, compressionLevel, testsPerCycle, tester->AverageResults());
	
	//	k++;
	//	compressionLevel--;
	
	//	delete tester;
	//}
	//
	
	//ex->Write();
	
	////Menu menu;
	
	
	//ex->Close();
	//delete ex;

#pragma endregion

	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);