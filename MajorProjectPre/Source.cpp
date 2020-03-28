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
#include "Test.h"
#include "Exporter.h"

#pragma endregion


#pragma endregion


// for some reason the data is not getting written out to the csv file

int main()
{
	Test* tester;
	Exporter* ex = new Exporter("test.csv");


	int compressionLevel = 100;
	int numberOfTests = 3;

	int k = 0;


	for (int i = 0; i < numberOfTests; i++)
	{
		tester = new Test(5, compressionLevel);
	
		ex->AddData(i, compressionLevel, numberOfTests, tester->AverageResults());

		ex->Write(k);

		k++;
		compressionLevel--;

		delete tester;
	}
	

	

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