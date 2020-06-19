#include "Menu.h"


#pragma region Constructors

Menu::Menu()
{
	currentUserFile = "";



	messageSize = 0;

	imageSamplePathBMP = "C:\\GitHub\\MajorProject\\ImageSamples\\BMP";
	imageSamplePathJPEG = "C:\\GitHub\\MajorProject\\ImageSamples\\JPEG";
	projectDirectory = "C:\\GitHub\\MajorProject\\MajorProjectPre";
	messagePath = "C:\\GitHub\\MajorProject\\MessageSamples";

	StartUpMessage();

	InitialSelection();
}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

void Menu::ClearScreen()
{
	system("cls");
}

void Menu::StartUpMessage()
{
	std::cout << "This program allows you to create BMP images and embed them with data." << std::endl;
	std::cout << "Decoding BMP and JPEG's is also possible." << std::endl;
}

void Menu::InitialSelection()
{
	unsigned int userChoice = 0;

	if (currentUserFile != "")
	{
		std::cout << std::endl << "Current file selected: " << currentUserFile << std::endl << std::endl;
	}

	if (currentUserMessage != "")
	{
		std::cout << std::endl << "Current file selected: " << currentUserMessage << std::endl << std::endl;
	}


	std::cout << std::endl << "Please choose an option by entering the associated number: " << std::endl << std::endl;

	std::cout << "1 - Create a new BMP" << std::endl;
	std::cout << "2 - Import an existing BMP" << std::endl;
	std::cout << "3 - Embed a message into a BMP" << std::endl;
	std::cout << "4 - Convert a BMP into a JPEG" << std::endl;
	std::cout << "5 - Extract a message from a JPEG" << std::endl;

	std::cin >> userChoice;

	MapChoice(userChoice);
}

void Menu::MapChoice(unsigned int userChoice)
{
	Action userAction = static_cast<Action>(userChoice);

	if (currentUserFile != "")
	{
		std::cout << std::endl << "Current file selected: " << currentUserFile << std::endl;
	}

	if (currentUserMessage != "")
	{
		std::cout << std::endl << "Current message selected: " << currentUserMessage << std::endl;
	}

	switch (userAction)
	{
	case Action::CREATE:
	{
		ClearScreen();

		Create();

		ClearScreen();

		InitialSelection();

		break;
	}
	case Action::IMPORT:

		ClearScreen();

		SearchFilesByExtension(imageSamplePathBMP, filePathList, ".bmp", ".BMP");
		SearchFilesByExtension(projectDirectory, filePathList, ".bmp", ".BMP");

		ListFiles();

		ClearScreen();

		InitialSelection();
		
		break;
	case Action::EMBED:

		if (currentUserFile == "")
		{
			std::cout << "No file selected: import a file first" << std::endl;

			ClearScreen();

			InitialSelection();

			break;
		}
		else
		{
			ClearScreen();

			MessageMenu();

			FileLoader messageLoader(currentUserMessagePath.c_str());

			FileLoader imageLoader(currentUserFilePath.c_str());

			std::string newFileName = NewFileName();

			std::cout << "Select a modulus value:" << std::endl;

			std::cin >> modValue;

			Stego stegoImage(&imageLoader, &messageLoader, newFileName.c_str(), MethodMenu(), modValue);

			messageSize = stegoImage.GetTextBuffer().GetBuffer().size();

			filePathList.push_back(std::pair(projectDirectory + "\\", newFileName));

			currentUserFile = newFileName;
			currentUserFilePath = projectDirectory + "\\" + newFileName;

			ClearScreen();

			std::cout << std::endl << "Message: " << "'" << currentUserMessage << "'" << " successfully embedded into "
				<< "'" << currentUserFile << "'" << std::endl;

			InitialSelection();
		}

		break;
	case Action::CONVERT:
	{
		ClearScreen();

		if (currentUserFilePath != "")
		{
			FileLoader fl(currentUserFilePath.c_str());

			BMP bmp(&fl);

			JPEGio jpegHandler(&fl);

			int compressionLevel = 0;
			std::cout << "Enter the level of compression quality required (0-100%): " << std::endl;
			std::cin >> compressionLevel;

			jpegHandler.BMPtoJPEG(&bmp, compressionLevel);

			InitialSelection();
		}
		else
		{
			std::cout << "You must first import a BMP file from the main menu." << std::endl;

			InitialSelection();
		}

		break;
	}
	case Action::DECODEJPEG:
	{
		ClearScreen();

		SearchFilesByExtension(imageSamplePathJPEG, filePathList, ".jpg");
		SearchFilesByExtension(projectDirectory, filePathList, ".jpg");

		ListFiles();

		FileLoader fl(currentUserFilePath.c_str());

		JPEGio jpegreader(&fl);

		JPEG jpeg(&jpegreader);

		Decoder d(&jpeg, MethodMenu(), messageSize, modValue);

		d.PrintMessage();

		InitialSelection();

		break;
	}
	}
}

void Menu::Create()
{
	std::string newFileName;
	unsigned int height, width, r, g, b;

	std::cout << "Enter name for new file (include .bmp file extention): " << std::endl;
	std::cin >> newFileName;

	std::cout << "Enter height for new image: " << std::endl;
	std::cin >> height;

	std::cout << "Enter width for new image: " << std::endl;
	std::cin >> width;

	std::cout << "Enter red, green and blue values (0-255) - (hit 'enter' after each value)" << std::endl;
	std::cin >> r;
	std::cin >> g;
	std::cin >> b;

	BMPWriter imageCreator;

	imageCreator.CreateNewBMP(newFileName.c_str(), width, height, RGB(r, g, b));
}

bool Menu::SearchExtension(std::filesystem::directory_entry file, std::string extension)
{
	// if the extension of the current file matches the argument return true, else return false
	return std::filesystem::path(file).extension() == extension;
}

// Searches for one file with the desired extention (this will be used with the variadic function to ensure that the last file is found)
template<class T> void Menu::SearchFilesByExtension(std::string path, std::vector<std::pair<std::string, std::string>>& container, T extension)
{
	// Iterate through all files in a specified directory
	for (const auto& file : std::filesystem::directory_iterator(path))
	{
		// If the extension of the current file matches an argument from list of arguments, step in
		if (SearchExtension(file, extension))
		{
			// Add both the file path and the file name to the vector in the form of a pair
			container.push_back(std::pair<std::string, std::string>(std::filesystem::path(file).string(), std::filesystem::path(file).filename().string()));
		}
	}
}

// Variadic function to search for X number of file extensions
template<class T, class... Ts> void Menu::SearchFilesByExtension(std::string path, std::vector<std::pair<std::string, std::string>>& paths, T extension, Ts... extensions)
{
	SearchFilesByExtension(path, paths, extension);

	SearchFilesByExtension(path, paths, extensions...);
}

void Menu::ListFiles()
{
	unsigned int userChoiceFile = 0;

	std::cout << "Select a file via the number associated with it: " << std::endl << std::endl;

	for (int i = 0; i < filePathList.size(); i++)
	{
		std::cout << i << " - " << filePathList[i].second << std::endl;
	}

	std::cin >> userChoiceFile;

	currentUserFilePath = filePathList[userChoiceFile].first;
	currentUserFile = filePathList[userChoiceFile].second;

	filePathList.clear();
}

void Menu::ListMessages()
{
	unsigned int userChoiceMessage = 0;

	std::cout << "Select a message via the number associated with it: " << std::endl << std::endl;

	for (int i = 0; i < messagePathList.size(); i++)
	{
		std::cout << i << " - " << messagePathList[i].second << std::endl;
	}

	std::cin >> userChoiceMessage;
	
	currentUserMessagePath = messagePathList[userChoiceMessage].first;
	currentUserMessage = messagePathList[userChoiceMessage].second;
	
	messagePathList.clear();
}

unsigned int Menu::MessageMenu()
{
	unsigned int importOption = 0;

	std::cout << "Would you like to import a message: " << std::endl;

	std::cout << "1 - yes" << std::endl;
	std::cout << "2 - no" << std::endl;

	std::cin >> importOption;

	switch (importOption)
	{
	case 1:
	{
		SearchFilesByExtension(messagePath, messagePathList, ".txt", ".TXT");
		SearchFilesByExtension(projectDirectory, messagePathList, ".txt", ".TXT");

		ListMessages();

		ClearScreen();

		break;
	}
	case 2:

		std::cout << "Not yet working" << std::endl;

		ClearScreen();

		MessageMenu();

		break;
	default:

		std::cout << "Invalid choice selection, choose again" << std::endl;

		ClearScreen();

		MessageMenu();

		break;
	}

	return 2;
}

std::string Menu::NewFileName()
{
	std::string fileName;

	std::cout << std::endl << "Enter a name for the new image: (include .bmp)" << std::endl;

	std::cin >> fileName;

	return fileName;
}

Method Menu::MethodMenu()
{
	int userChoice = 0;

	std::cout << "Select which steganographic method you would like to use:" << std::endl << std::endl;

	std::cout << "0 - Least Significant Bit" << std::endl;
	std::cout << "1 - Distance-to-Origin" << std::endl;

	std::cin >> userChoice;

	ClearScreen();

	return static_cast<Method>(userChoice);
}

#pragma endregion