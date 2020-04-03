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
	Test* tester;
	Exporter* ex = new Exporter("Test01 - 100%-91%.csv");


	int compressionLevel = 100;
	int numberOfCycles = 10;
	int testsPerCycle = 30;

	int k = 0;


	for (int j = 0; j < numberOfCycles; j++)
	{
		tester = new Test(testsPerCycle, compressionLevel);

		ex->AddData(j, compressionLevel, testsPerCycle, tester->AverageResults(), tester->totalCharacters, tester->matchedCharacters);

		k++;
		compressionLevel--;

		delete tester;
	}
	
	


	ex->Write();

	//Menu menu;


	ex->Close();
	delete ex;
	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);