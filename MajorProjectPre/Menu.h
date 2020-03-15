#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "BMPWriter.h"
#include "Stego.h"

enum class Method
{
	DTO, LSB
};

enum class Image
{
	BMP, JPEG
};

enum class Action
{
	CREATE = 1, IMPORT, EMBED, DECODEJPEG
};

class Menu
{
#pragma region Attributes

private:
	unsigned int fileCount;

	std::string currentUserFile;

	std::string currentUserFilePath;

	std::string currentUserMessage;

	std::string currentUserMessagePath;

	std::vector<std::pair<std::string, std::string>> filePathList;

	std::vector<std::pair<std::string, std::string>> messagePathList;

#pragma endregion

#pragma region Constructors

public:
	Menu();

#pragma endregion

#pragma region Properties

public:

#pragma endregion

#pragma region Methods

public:
	void StartUpMessage();

	void InitialSelection();

	void MapChoice(unsigned int userChoice);

	void ClearScreen();

	void Create();

	void SearchFiles();

	void ListFiles();

	void ListMessages();
	
	unsigned int MessageMenu();

	std::string NewFileName();

#pragma endregion
};

