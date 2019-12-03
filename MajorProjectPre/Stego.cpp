#include "Stego.h"


#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileReader* coverBMP, FileReader* textFile) 
	: bmp(coverBMP), text(textFile)
{
	CreatePixelListCopy();

	CreateBinaryList(text);

	LSB();

	ModifyBMP(&bmp, "new.bmp");
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
	pixelListCopy = std::vector<std::vector<RGB>>(bmp.GetHeight(), std::vector<RGB>(bmp.GetWidth()));

	for(int i = 0; i < bmp.GetHeight(); i++)
	{
		for(int j = 0; j < bmp.GetWidth(); j++)
		{
			pixelListCopy[i][j].SetRed(*bmp.GetPixelContainer()->GetRed(j));

			pixelListCopy[i][j].SetGreen(*bmp.GetPixelContainer()->GetGreen(j));

			pixelListCopy[i][j].SetBlue(*bmp.GetPixelContainer()->GetBlue(j));
		}
	}
}

void Stego::LSB()
{
	// access to the list of pixels
	// access to the list of binary text

	// loop through each of the rgb elements of each pixel
		// compare whether the LSB is the same as each binary component

	// Change if needed / leave if not


	for(int i = 0; i < bmp.GetHeight() * bmp.GetWidth(); i++)
	{
		// Print binary of current RED value
		std::cout << std::bitset<8>(*bmp.GetPixelContainer()->GetGreen(i)) << std::endl;

		// Print the LSB of the first char
		std::cout << std::bitset<1>(binaryList.data()[i][0]) << std::endl << std::endl;

		// At the point where i am trying to take each binary value and check it against the binary value stored in 
		// each RGB value of the image.

		int j = 0;

		for(int i = 0; i < GetBinaryListSize(); i++)
		{
			if((*bmp.GetPixelContainer()[i].GetRed(j) % 2) != 0 && (binaryList[i][j] % 2) != 0)
			{
				bmp.GetPixelContainer()[i].SetRed(*bmp.GetPixelContainer()[i].GetRed(j) ^= 1, j);
			}
		
			if((*bmp.GetPixelContainer()[i].GetGreen(j) % 2) != 0 && (binaryList[i][j] % 2) != 0)
			{
				bmp.GetPixelContainer()[i].SetGreen(*bmp.GetPixelContainer()[i].GetGreen(j + 1) ^= 1, j);
			}

			if((*bmp.GetPixelContainer()[i].GetBlue(j) % 2) != 0 && (binaryList[i][j] % 2) != 0)
			{
				bmp.GetPixelContainer()[i].SetBlue(*bmp.GetPixelContainer()[i].GetBlue(j) ^= 1, j);
			}

			j += 3;
		}


#pragma region blanked
		//// Red
		//if(((*bmp.GetPixelContainer()->GetRed(i) % 2) == 0) && (binaryList.data()[i][0]) == 0)
		//{
		//	std::cout << std::bitset<8>(*bmp.GetPixelContainer()->GetRed(i)) << std::endl << std::endl;

		//	continue;
		//}
		//else
		//{
		//	bmp.GetPixelContainer()->SetRed(*bmp.GetPixelContainer()->GetRed(i) ^= 1, i);

		//	std::cout << std::bitset<8>(*bmp.GetPixelContainer()->GetRed(i)) << std::endl << std::endl;
		//}

		//// Green
		//if(((*bmp.GetPixelContainer()->GetGreen(i) % 2) == 0) && (binaryList.data()[i][0]) == 0)
		//{
		//	std::cout << std::bitset<8>(*bmp.GetPixelContainer()->GetGreen(i)) << std::endl << std::endl;

		//	continue;
		//}
		//else
		//{
		//	bmp.GetPixelContainer()->SetGreen(*bmp.GetPixelContainer()->GetGreen(i) ^= 1, i);

		//	std::cout << std::bitset<8>(*bmp.GetPixelContainer()->GetGreen(i)) << std::endl << std::endl;
		//}
#pragma endregion


		
	}

}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	for(int i = 0; i < bmp->GetHeight() * bmp->GetWidth(); i++)
	{
		pixelContainer.SetRed((unsigned char*)bmp->GetPixelContainer()->GetRed(i), i);

		/*std::cout << std::bitset<8>(*pixelContainer.GetRed(i)) << std::endl;

		pixelContainer.SetRed(*bmp->GetPixelContainer()->GetRed(i) ^= 1, i);

		std::cout << std::bitset<8>(*pixelContainer.GetRed(i)) << std::endl;*/

		pixelContainer.SetGreen((unsigned char*)bmp->GetPixelContainer()->GetGreen(i), i);
		pixelContainer.SetBlue((unsigned char*)bmp->GetPixelContainer()->GetBlue(i), i);
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	std::cout << "Image generated" << std::endl;

	fclose(bmp->GetFileObject()->GetFile());
}


#pragma endregion