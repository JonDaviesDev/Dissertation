#include "Decoder.h"


#pragma region Constructors

Decoder::Decoder(BMP* stegoImage) : newTextFile(nullptr), messageBinary(4, 0)
{
	RetrieveMessage(stegoImage);
	
	decodedMessage = ConstructMessage();
}

Decoder::Decoder(JPEG* stegoImage) : newTextFile(nullptr), messageBinary(4, 0)
{
	RetrieveMessage(stegoImage);

	decodedMessage = ConstructMessage();
}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void Decoder::RetrieveMessage(BMP* image)
{
	int k = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			RGB element((float)*image->GetPixelContainer()->GetRed(k), (float)*image->GetPixelContainer()->GetGreen(k), (float)*image->GetPixelContainer()->GetBlue(k));

			int remainder = RoundToInt(FindLength(element));

			if(DetermineSegment(FindModulus(remainder, 42), 42) == 0)
			{
				messageBinary[i][j] = 0;
			}
			else
			{
				messageBinary[i][j] = 1;
			}

			k++;
		}
	}
}

void Decoder::RetrieveMessage(JPEG* image)
{
	int k = 0;

	unsigned char* temp = image->GetPixelList()->GetPixelArray();

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			RGB element(temp, k);

			

			int remainder = RoundToInt(FindLength(element));

			if(DetermineSegment(FindModulus(remainder, 42), 42) == 0)
			{
				messageBinary[i][j] = 0;
			}
			else
			{
				messageBinary[i][j] = 1;
			}

			k+=3;
		}
	}
}

char Decoder::BinaryToChar(std::bitset<8> byte)
{
	return static_cast<char>(std::bitset<8>(byte).to_ulong());
}

std::string Decoder::ConstructMessage()
{
	std::string message = "";

	for(int i = 0; i < messageBinary.size(); i++)
	{
		message += BinaryToChar(messageBinary[i]);
	}

	return message;
}

#pragma endregion
