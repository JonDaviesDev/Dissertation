#include "Test.h"


#pragma region Constructors

Test::Test(int numberOfTests, int compressionRatio)
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

		

		// Create String
		// Set the size of the string
		int stringSize = Random(4, 50).value;

		std::string originalMessage = "";

		// Until the size of the string has been reached, loop
		for (int i = 0; i < stringSize; i++)
		{
			// Add a random character to the string (97-122 = a-z in ASCII)
			originalMessage += (char)Random(97, 122).value;
		}

		int messageSize = originalMessage.size();

		


		// Embed


		Stego s(&imageFileLoader, &originalMessage, newFileName.c_str(), 1);






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

#pragma endregion

#pragma region Methods
//
//void Test::CreateNewBMP()
//{
//	BMPWriter writer;
//
//	const char* fileName = "test.bmp";
//
//	writer.CreateNewBMP(fileName, 512, 512, RGB(Random(10, 245).value, Random(10, 245).value, Random(10, 245).value));
//	
//	FileLoader fl(fileName);
//
//	newBMP = new BMP(&fl);
//}
//
//std::string Test::CreateMessage()
//{
//	// Set the size of the string
//	int stringSize = Random(4, 50).value;
//
//	std::string temp = "";
//
//	// Until the size of the string has been reached, loop
//	for (int i = 0; i < stringSize; i++)
//	{
//		// Add a random character to the string (97-122 = a-z in ASCII)
//		temp += (char)Random(97, 122).value;
//	}
//
//	return temp;
//}
//
//void Test::EmbedBMP(std::string* message)
//{
//	const char* newFileName = "testEmbed.bmp";
//
//	Stego s(newBMP, message, newFileName, 1);
//
//	FileLoader fl(newFileName);
//
//	embeddedBMP = new BMP(&fl);
//}
//
//JPEG Test::ConvertToJPEG(int compressionLevel)
//{
//	// cant get access to the file name for read pixels
//
//	int a = 3;
//
//  	FileLoader fl(embeddedBMP->GetFileObject()->GetFileName());
//
//	JPEGio jpio(&fl, compressionLevel);
//
//	const char* temp = jpio.GetFileName();
//
//	JPEG jpg(jpio, jpio.GetFileName());
//
//	return jpg;
//}
//
float Test::CompareResults(std::string originalMessage, std::string decodedMessage)
{
	int messageSize = originalMessage.size();
	int matchedCharacters = 0;

	for (int i = 0; i < originalMessage.size(); i++)
	{
		if (originalMessage[i] == decodedMessage[i])
		{
			matchedCharacters++;
		}
	}

	return (float)matchedCharacters / (float)messageSize * 100;
}


void Test::DecodeJPEG(JPEG* jpeg, int messageSize, int compressionRatio, std::string originalMessage)
{
	Decoder decoder(jpeg, 1, messageSize);

	float similarity = CompareResults(originalMessage, decoder.GetDecodedMessage());

	Dimension imageData(jpeg->GetImageData().GetValues());

	currentResult = Result(results.size(), similarity, compressionRatio, imageData);

	
}

void Test::UpdateVector()
{
	results.push_back(currentResult);
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