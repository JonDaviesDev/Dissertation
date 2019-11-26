#include "Stego.h"


#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileReader* coverBMP, FileReader* textFile) : bmp(coverBMP), text(textFile)
{
	CreateBinaryList(text);
}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

std::bitset<8> Stego::CharToBinary(char value)
{
	return std::bitset<8>(value);
}

void Stego::CreateBinaryList(TextBuffer buffer)
{
	for(int i = 0; i < buffer.GetBuffer().size(); i++)
	{
		binaryList.push_back(CharToBinary(buffer.GetBuffer()[i]));
	}
}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	for(int i = 0; i < bmp->GetHeight() * bmp->GetWidth(); i++)
	{
		pixelContainer.SetRed((unsigned char*)bmp->GetPixelContainer()->GetRed(i), i);
		pixelContainer.SetGreen((unsigned char*)bmp->GetPixelContainer()->GetGreen(i), i);
		pixelContainer.SetBlue((unsigned char*)bmp->GetPixelContainer()->GetBlue(i), i);
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	std::cout << "Image generated" << std::endl;

	fclose(bmp->GetFileObject()->GetFile());
}


#pragma endregion