#include "BMP.h"
#include <string>

int main()
{
	const char* fileName = {"C:\\Users\\jonny\\source\\repos\\MajorProject\\MajorProjectPre\\ImageSamples\\stripes.BMP"};

	BMP* myBMP = new BMP();

	myBMP->ScanBMP(fileName, "rb");

	myBMP->Write(fileName);

	return 0;
}
