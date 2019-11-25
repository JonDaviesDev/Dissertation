#include "File.h"

#pragma region Constructors

File::File() {}

#pragma endregion

#pragma region Methods

FILE* File::ErrorCheck(FILE* file, const char* filePath, const char* mode)
{
	errno_t error = NULL;
	char errorMessageBuffer[95];	// Maximum error message length is 94 chars. +1 for null terminator

	if((error = fopen_s(&file, filePath, mode)) != 0)
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "Cannot open file '" << filePath << "' : " << errorMessageBuffer << std::endl;

		return NULL;
	}

	else
	{
		strerror_s(errorMessageBuffer, sizeof(errorMessageBuffer), error);

		std::cout << "'" << filePath << "' " << "opened successfully in '" << mode << "' mode" << std::endl;
		std::cout << errorMessageBuffer << std::endl;

		return file;
	}
}

#pragma endregion

