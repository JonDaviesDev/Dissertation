#include "TextBuffer.h"
#include <string>
#include <istream>


#pragma region Constructors

TextBuffer::TextBuffer() {}

TextBuffer::TextBuffer(FileLoader* textFile)
{
	ReadFile(textFile);
}

#pragma endregion

#pragma region Properties

std::vector<char> TextBuffer::GetBuffer() { return buffer; }

#pragma endregion

#pragma region Methods

void TextBuffer::ReadFile(FileLoader* textFile)
{
	textFile->ErrorCheck(textFile->GetFile(), textFile->GetFileName(), "rb");

	char tempBuffer;

	while(fscanf_s(textFile->GetFile(), "%c", &tempBuffer, sizeof(char)) != EOF)
	{
		buffer.push_back(tempBuffer);
	}
		
}



#pragma endregion
