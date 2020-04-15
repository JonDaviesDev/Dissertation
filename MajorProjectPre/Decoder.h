#pragma once

#pragma region Preprocessor Directives

#pragma region System Files

#include <iostream>
#include <bitset>
#include <vector>

#pragma endregion

#pragma region Project Files

#include "BMP.h"
#include "JPEG.h"
#include "StegoMath.h"

#pragma endregion

#pragma endregion

class Decoder : public StegoMath
{
#pragma region Attributes

private:
	FILE* newTextFile;

	std::vector<std::bitset<8>> messageBinary;

	std::string decodedMessage;

#pragma endregion

#pragma region Constructors

public:
	Decoder(BMP* stegoImage, Method method);

	Decoder(JPEG* stegoImage, Method method);

	Decoder(JPEG* stegoImage, Method method, int messageSize, int modValue); // Constructor for testing

#pragma endregion

#pragma region Properties

public:
	std::string GetDecodedMessage();

#pragma endregion

#pragma region Methods

public:
	void RetrieveMessageDTO(BMP* image);

	void RetrieveMessageDTO(JPEG* image);

	void RetrieveMessageDTOTesting(JPEG* image, int messageSize, int modValue);

	void RetrieveMessageLSB(BMP* image);

	void RetrieveMessageLSB(JPEG* image);

	void RetrieveMessageLSBTesting(JPEG* image, int messageSize);

	char BinaryToChar(std::bitset<8> byte);

	std::string ConstructMessage();

#pragma endregion
};

