#include "Menu.h"


#pragma region Constructors

Menu::Menu()
{
	currentUserFile = "";

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
	std::cout << "4 - Extract a message from a JPEG" << std::endl;

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

		SearchFiles();

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

			Stego stegoImage(&imageLoader, &messageLoader, NewFileName().c_str());

			ClearScreen();

			std::cout << std::endl << "Message: " << currentUserMessage << " successfully embedded into "
				<< "'" << currentUserFile << "'" << std::endl;

			InitialSelection();
		}

		break;
	case Action::DECODEJPEG:

		break;
	}
}

void Menu::Create()
{
	std::string newFileName;
	unsigned int height, width, r, g, b;

	std::cout << "Enter name for new file: " << std::endl;
	std::cin >> newFileName;

	std::cout << "Enter height for new image: " << std::endl;
	std::cin >> height;

	std::cout << "Enter width for new image: " << std::endl;
	std::cin >> width;

	std::cout << "Enter red, green and blue values (0-255)" << std::endl;
	std::cin >> r;
	std::cin >> g;
	std::cin >> b;

	BMPWriter imageCreator;

	imageCreator.CreateNewBMP(newFileName.c_str(), width, height, RGB(r, g, b));

	std::cout << "Image created" << std::endl;
}

void Menu::SearchFiles()
{
	std::string imageSamplePath = "C:\\GitHub\\MajorProject\\ImageSamples\\BMP";
	std::string projectDirectory = "C:\\GitHub\\MajorProject\\MajorProjectPre";

	int fileCount = 0;

	for (const auto& file : std::filesystem::directory_iterator(imageSamplePath))
	{
		if (std::filesystem::path(file).extension() == ".bmp" || std::filesystem::path(file).extension() == ".BMP")
		{
			filePathList.push_back(std::pair<std::string, std::string>(std::filesystem::path(file).string(), std::filesystem::path(file).filename().string()));

			fileCount++;
		}
	}

	for (const auto& file : std::filesystem::directory_iterator(projectDirectory))
	{
		if (std::filesystem::path(file).extension() == ".bmp" || std::filesystem::path(file).extension() == ".BMP")
		{
			filePathList.push_back(std::pair<std::string, std::string>(std::filesystem::path(file).string(), std::filesystem::path(file).filename().string()));

			fileCount++;
		}
	}
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
		std::string messagePath = "C:\\GitHub\\MajorProject\\MessageSamples";

		for (const auto& file : std::filesystem::directory_iterator(messagePath))
		{
			if (std::filesystem::path(file).extension() == ".txt" || std::filesystem::path(file).extension() == ".TXT")
			{
				messagePathList.push_back(std::pair<std::string, std::string>(std::filesystem::path(file).string(), std::filesystem::path(file).filename().string()));
			}
		}

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

	std::cout << std::endl << "Enter a name for the new image: " << std::endl;

	std::cin >> fileName;

	return fileName;
}

#pragma endregion