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

#pragma endregion