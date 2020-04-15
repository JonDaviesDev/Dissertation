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
	Exporter* ex = new Exporter("Mod242 - 10.csv"); 

	int compressionLevel = 10;
	int numberOfCycles = 10;
	int testsPerCycle = 30;
	Method currentMethod = Method::DTO;

	int modulus = 242;

	int k = 0;

	for (int j = 0; j < numberOfCycles; j++)
	{
		tester = new Test(testsPerCycle, compressionLevel, modulus, currentMethod);

		ex->AddData(j, compressionLevel, testsPerCycle, tester->AverageResults());

		k++;
		compressionLevel--;

		delete tester;
	}
	

	ex->Write();

	//Menu menu;


	ex->Close();
	delete ex;

	/*BMPWriter writer;

	writer.CreateNewBMP("Mod142.bmp", 512, 512, RGB(30, 30, 200));

	FileLoader fl("Mod142.bmp");
	FileLoader mfl("test.txt");

	Stego s(&fl, &mfl, "embeddedMod142.bmp", Method::DTO, 142);



	FileLoader efl("embeddedMod142.bmp");

	BMP embeddedBMP(&efl);

	JPEGio jpio(&efl);

	jpio.BMPtoJPEG(&embeddedBMP, 100);*/




	return 0;
}




















//// Create stego file
//FileReader image(TESTPATH);



//Stego st(&image, &text);




//// Read new file to make sure it works
//FileReader newFile("C:\\GitHub\\MajorProject\\MajorProjectPre\\newStegoTest.bmp");

//BMP newBMP(&newFile);