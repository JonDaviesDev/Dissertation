#include "Test.h"


#pragma region Constructors

Test::Test(int numberOfTests) {}

#pragma endregion

#pragma region Properties

#pragma endregion

#pragma region Methods

BMP* Test::CreateNewBMP()
{
	BMPWriter writer;

	std::string fileName = "test.bmp";

	writer.CreateNewBMP(fileName.c_str(), 512, 512, RGB(Random(10, 245).value, Random(10, 245).value, Random(10, 245).value));
	
	return &BMP(&FileLoader(fileName.c_str()));
}

std::string* Test::CreateMessage()
{
	// Set the size of the string
	int stringSize = Random(4, 50).value;

	std::string temp = "";

	// Until the size of the string has been reached, loop
	for (int i = 0; i < stringSize; i++)
	{
		// Add a random character to the string (97-122 = a-z in ASCII)
		temp += (char)Random(97, 122).value;
	}

	return &temp;
}

BMP* Test::EmbedBMP(BMP* bmp, std::string* message)
{
	std::string newFileName = "testEmbed.bmp";

	Stego s(bmp, message, newFileName.c_str(), 1);

	return &BMP(&FileLoader(newFileName.c_str()));
}

JPEG* Test::ConvertToJPEG(BMP* bmp)
{
	return &JPEG(&JPEGio(bmp));
}

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

Result Test::DecodeJPEG(JPEG* jpeg, int messageSize, std::string originalMessage)
{
	Decoder decoder(jpeg, 1, messageSize);

	float similarity = CompareResults(originalMessage, decoder.GetDecodedMessage());

	Dimension imageData(jpeg->GetImageData().GetValues());

	return Result(similarity, 2, imageData);
}

void Test::UpdateVector(Result result)
{
	result.id = results.size();

	results.push_back(result);
}

#pragma endregion