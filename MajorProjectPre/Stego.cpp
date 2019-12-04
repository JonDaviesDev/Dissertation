#include "Stego.h"


#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileReader* coverBMP, FileReader* textFile) 
	: bmp(coverBMP), text(textFile)
{
	CreatePixelListCopy();

	CreateBinaryList(text);

	LSB();

	ModifyBMP(&bmp, "newStegoTest.bmp");
}

#pragma endregion

#pragma region Properties

#pragma region Setters



#pragma endregion

#pragma region Getters

int Stego::GetBinaryListSize()
{
	int size = 0;

	for(int i = 0; i < binaryList.size(); i++)
	{
		size += 8;
	}

	return size;
}

#pragma endregion

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

void Stego::CreatePixelListCopy()
{
	pixelList = std::vector<std::vector<RGB>>(bmp.GetHeight(), std::vector<RGB>(bmp.GetWidth()));

	for(int i = 0; i < bmp.GetHeight(); i++)
	{
		for(int j = 0; j < bmp.GetWidth(); j++)
		{
			pixelList[i][j].SetRed(*bmp.GetPixelContainer()->GetRed(j));

			pixelList[i][j].SetGreen(*bmp.GetPixelContainer()->GetGreen(j));

			pixelList[i][j].SetBlue(*bmp.GetPixelContainer()->GetBlue(j));
		}
	}
}

void Stego::LSB()
{
	int k = 0;

	for(int i = 0; i < binaryList.size(); i++)
	{
		for(int j = 0; j < binaryList[i].size(); j++)
		{
			if((pixelList[0][k].GetRed() % 2) != 0 && (binaryList[i][j] % 2) != 0)
			{
				unsigned char temp = pixelList[i][j].GetRed();
			
				pixelList[0][k].SetRed(temp ^= 1);
			}
			
			k++;
		}
	}
}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	int k = 0;

	for(int i = 0; i < bmp->GetHeight(); i++)
	{
		for(int j = 0; j < bmp->GetWidth(); j++)
		{
			pixelContainer.SetRed(pixelList[i][j].GetRed(), k);

			pixelContainer.SetGreen(pixelList[i][j].GetGreen(), k);

			pixelContainer.SetBlue(pixelList[i][j].GetBlue(), k);

			k++;
		}
		
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	std::cout << "Image generated" << std::endl;

	fclose(bmp->GetFileObject()->GetFile());
}

#pragma endregion