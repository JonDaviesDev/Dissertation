#include "Decoder.h"


#pragma region Constructors

Decoder::Decoder(BMP* stegoImage, Method method) : newTextFile(nullptr), messageBinary(43, 0)
{
	if(method == Method::DTO)
	{
		RetrieveMessageDTO(stegoImage);
	}
	else if (method == Method::LSB)
	{
		RetrieveMessageLSB(stegoImage);
	}

	decodedMessage = ConstructMessage();
}

Decoder::Decoder(JPEG* stegoImage, Method method) : newTextFile(nullptr), messageBinary(43, 0)
{
	if(method == Method::DTO)
	{
		RetrieveMessageDTO(stegoImage);
	}
	else RetrieveMessageLSB(stegoImage);

	decodedMessage = ConstructMessage();
}

Decoder::Decoder(JPEG* stegoImage, Method method, int messageSize, int modValue) : newTextFile(nullptr), messageBinary(messageSize, 0)
{
	if (method == Method::DTO)
	{
		RetrieveMessageDTOTesting(stegoImage, messageSize, modValue);
	}
	else if (method == Method::LSB)
	{
		RetrieveMessageLSBTesting(stegoImage, messageSize);
	}

	decodedMessage = ConstructMessage();
}

#pragma endregion

#pragma region Properties

std::string Decoder::GetDecodedMessage() { return decodedMessage; }

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

	// for each character in the message
	for(int i = 0; i < 43; i++)
	{
		// for each bit that makes up that character
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

void Decoder::RetrieveMessageDTOTesting(JPEG* image, int messageSize, int modValue)
{
	int k = 0;

	unsigned char* temp = image->GetPixelList()->GetPixelArray();

	// for each character in the message
	for (int i = 0; i < messageSize; i++)
	{
		// for each bit that makes up that character
		for (int j = 0; j < 8; j++)
		{
			RGB element(temp, k);

			int remainder = RoundToInt(FindLength(element));

			if (DetermineSegment(FindModulus(remainder, modValue), modValue) == 0)
			{
				messageBinary[i][j] = 0;
			}
			else
			{
				messageBinary[i][j] = 1;
			}

			k += 3;
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

void Decoder::RetrieveMessageLSBTesting(JPEG* image, int messageSize)
{
	int k = 0;

	for (int i = 0; i < messageSize; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			int tempRed = (int)image->GetPixelList()->GetPixelArray()[k];

			if (tempRed % 2 == 0)
			{
				messageBinary[i][j] = 0;
			}
			else
			{
				messageBinary[i][j] = 1;
			}

			k += 3;
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
