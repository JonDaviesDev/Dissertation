#include "Decoder.h"


#pragma region Constructors

Decoder::Decoder(BMP* stegoImage, unsigned int flag) : newTextFile(nullptr), messageBinary(4, 0)
{
	if(FlagChoice(flag))
	{
		RetrieveMessageDTO(stegoImage);
	}
	else RetrieveMessageLSB(stegoImage);

	decodedMessage = ConstructMessage();
}

Decoder::Decoder(JPEG* stegoImage, unsigned int flag) : newTextFile(nullptr), messageBinary(4, 0)
{
	if(FlagChoice(flag))
	{
		RetrieveMessageDTO(stegoImage);
	}
	else RetrieveMessageLSB(stegoImage);

	decodedMessage = ConstructMessage();
}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void Decoder::RetrieveMessageDTO(BMP* image)
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

void Decoder::RetrieveMessageDTO(JPEG* image)
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

void Decoder::RetrieveMessageLSB(BMP* image)
{
	int k = 0;

	unsigned char* tempRed = nullptr;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			int tempRed = (int)*image->GetPixelContainer()->GetRed(k);

			if(tempRed % 2 == 0)
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

void Decoder::RetrieveMessageLSB(JPEG* image)
{
	int k = 0;

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			int tempRed = (int)image->GetPixelList()->GetPixelArray()[k];

			if(tempRed % 2 == 0)
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

bool Decoder::FlagChoice(unsigned int flag)
{
	if(flag == 1)
	{
		return true;
	}
	else if(flag == 0)
	{
		return false;
	}
}

#pragma endregion
