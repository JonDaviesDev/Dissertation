#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>

#include "BMPWriter.h"
#include "Stego.h"
#include "Decoder.h"

enum class Image
{
	BMP, JPEG
};

enum class Action
{
	CREATE = 1, IMPORT, EMBED, CONVERT, DECODEJPEG
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

	std::string imageSamplePathBMP;

	std::string imageSamplePathJPEG;

	std::string messagePath;

	std::string projectDirectory;

	std::vector<std::pair<std::string, std::string>> filePathList;

	std::vector<std::pair<std::string, std::string>> messagePathList;

	int messageSize;

	int modValue;

	bool imported;

	bool bmpToJPEG;

	bool embedded;

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

	bool SearchExtension(std::filesystem::directory_entry file, std::string extension);

	template<class T> void SearchFilesByExtension(std::string path, std::vector<std::pair<std::string, std::string>>& container, T extension);

	template<class T, class... Ts> void SearchFilesByExtension(std::string path, std::vector<std::pair<std::string, std::string>>& paths, T extension, Ts... extensions);

	void ListFiles();

	void ListMessages();
	
	unsigned int MessageMenu();

	std::string NewFileName();

	Method MethodMenu();

	Method MethodSelection(Method userChoice);

#pragma endregion
};

