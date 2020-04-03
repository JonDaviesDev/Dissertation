#include "Test.h"


#pragma region Constructors

Test::Test() {}

Test::Test(int numberOfTests, int compressionRatio, int modulusValue, std::string customMessage)
{
	std::string projectDirectory = "C:\\GitHub\\MajorProject\\MajorProjectPre\\";

	std::string fileName = "test.bmp";
	std::string newFileName = "testEmbed.bmp";
	std::string jpegName = "testEmbed.jpg";

	decodedMessage = "";

	for (int i = 0; i < numberOfTests; i++)
	{
		//Create Image
		BMPWriter writer;



		writer.CreateNewBMP(fileName.c_str(), 512, 512, RGB(Random(10, 245).value, Random(10, 245).value, Random(10, 245).value));

		FileLoader imageFileLoader(fileName.c_str());



		std::string originalMessage = "";
		int messageSize = 0;

		if (customMessage != "")
		{
			originalMessage = customMessage;
		}
		else
		{
			int stringSize = Random(4, 50).value;

			// Until the size of the string has been reached, loop
			for (int i = 0; i < stringSize; i++)
			{
				// Add a random character to the string (97-122 = a-z in ASCII)
				originalMessage += (char)Random(97, 122).value;
			}
		}

		messageSize = originalMessage.size();
		


		// Embed


		Stego s(&imageFileLoader, &originalMessage, newFileName.c_str(), 1, modulusValue);






		FileLoader embeddedFileLoader(newFileName.c_str());

		BMP embeddedBMP(&embeddedFileLoader);

		JPEGio jpio(&embeddedFileLoader);

		jpio.BMPtoJPEG(&embeddedBMP, compressionRatio);




		FileLoader fl(jpegName.c_str());

		JPEGio jpegreader(&fl);

		JPEG jpeg(&jpegreader);

		DecodeJPEG(&jpeg, messageSize, compressionRatio, originalMessage);




		UpdateVector();

		_fcloseall();


		DeleteImage(fileName);
		DeleteImage(newFileName);
		DeleteImage(jpegName);
	}
}

#pragma endregion

#pragma region Properties

std::vector<Result> Test::GetList() { return results; }

Result* Test::GetResults() { return &results[0]; }

#pragma endregion

#pragma region Methods

float Test::CompareResults(std::string originalMessage, std::string decodedMessage)
{
	totalCharacters = originalMessage.size();
	matchedCharacters = 0;

	for (int i = 0; i < originalMessage.size(); i++)
	{
		if (originalMessage[i] == decodedMessage[i])
		{
			matchedCharacters++;
		}
	}

	return (float)matchedCharacters / (float)totalCharacters * 100;
}

void Test::DecodeJPEG(JPEG* jpeg, int messageSize, int compressionRatio, std::string originalMessage)
{
	Decoder decoder(jpeg, 1, messageSize);

	float similarity = CompareResults(originalMessage, decoder.GetDecodedMessage());

	Dimension imageData(jpeg->GetImageData().GetValues());

	currentResult = Result(results.size(), similarity, matchedCharacters, messageSize, compressionRatio, imageData, originalMessage, decoder.GetDecodedMessage());
}

void Test::UpdateVector()
{
	results.push_back(currentResult);
}

float Test::AverageResults()
{
	float total = 0;

	for (int i = 0; i < results.size(); i++)
	{
		total += results[i].accuracy;
	}

	return total / results.size();
}

void Test::DeleteImage(std::string fileName)
{
	bool fileDeleted = false;

	std::string projectDirectoryPath = "C:\\GitHub\\MajorProject\\MajorProjectPre\\";

	std::remove(std::string(projectDirectoryPath + fileName).c_str());

	/*for (const auto& file : std::filesystem::directory_iterator(projectDirectoryPath))
	{
		if (std::filesystem::path(file).filename().string() == fileName)
		{
			std::filesystem::remove(std::filesystem::path(file));

			fileDeleted = true;
		}

		if (fileDeleted)
		{
			break;
		}
	}*/
}

#pragma endregion