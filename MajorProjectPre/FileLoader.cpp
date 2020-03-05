#include "FileLoader.h"


#pragma region Constructors

FileLoader::FileLoader() {}

FileLoader::FileLoader(const char* fileName) : file(fileName) 
{
	file.SetFile(ErrorCheck(file.GetFile(), file.GetName(), "r"));
}

FileLoader::FileLoader(FILE* file)
{
	this->file.SetFile(file);
}

#pragma endregion

#pragma region Properties

void FileLoader::SetName(const char* value) { file.SetName(value); }

FILE* FileLoader::GetFile() { return file.GetFile(); }

const char* FileLoader::GetFileName() { return file.GetName(); }

#pragma endregion


#pragma region Methods

FILE* FileLoader::ErrorCheck(FILE* file, const char* filePath, const char* mode)
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