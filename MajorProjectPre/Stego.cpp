#include "Stego.h"

#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileLoader* coverBMP, FileLoader* textFile, const char* newFileName, unsigned int LSBorDTO, int modValue)
	: bmp(coverBMP), text(textFile), stegoFileName(newFileName)
{
	informationContainer = PackData(text.GetBuffer().size() * 8, modValue);

	int k = 0;

	CreatePixelListCopy();

	CreateBinaryList(text);

	BitNumber();

	if (LSBorDTO == 1)
	{
		for (int i = 0; i < binaryList.size(); i++)
		{
			for (int j = 0; j < binaryList[i].size(); j++)
			{
				DistanceToOrigin(pixelList[0][k], modValue, binaryList[i][j]);

				k++;
			}
		}
	}
	else if (LSBorDTO == 0)
	{
		LSB();
	}
	else
	{
		exit(-1);
	}
	
	ModifyBMP(&bmp, newFileName);
}

Stego::Stego(FileLoader* coverBMP, std::string* text, const char* newFileName, unsigned int LSBorDTO, int modValue)
	: bmp(coverBMP), text(*text), stegoFileName(newFileName)
{
	informationContainer = PackData(this->text.GetBuffer().size() * 8, modValue);

	int k = 0;

	CreatePixelListCopy();

	CreateBinaryList(*text);

	BitNumber();

	if (LSBorDTO == 1)
	{
		for (int i = 0; i < binaryList.size(); i++)
		{
			for (int j = 0; j < binaryList[i].size(); j++)
			{
				DistanceToOrigin(pixelList[0][k], modValue, binaryList[i][j]);

				k++;
			}
		}
	}
	else if (LSBorDTO == 0)
	{
		LSB();
	}
	else
	{
		exit(-1);
	}

	ModifyBMP(&bmp, newFileName);
}

#pragma endregion

#pragma region Properties

#pragma region Setters



#pragma endregion

#pragma region Getters

int Stego::GetBinaryListSize()
{
	int size = 0;

	for(int i = 0; i < binaryList.size(); i++)
	{
		size += 8;
	}

	return size;
}

const char* Stego::GetStegoFileName() { return stegoFileName; }

TextBuffer Stego::GetTextBuffer() { return text; }

#pragma endregion

#pragma endregion

#pragma region Methods

// Convert a single char to its binary representation
std::bitset<8> Stego::CharToBinary(char value)
{
	return std::bitset<8>(value);
}

// Convert a string of text to binary and store in list
void Stego::CreateBinaryList(TextBuffer buffer)
{
	// for every element inside the text buffer
	for(int i = 0; i < buffer.GetBuffer().size(); i++)
	{
		// Covert it to binary and add to list
		binaryList.push_back(CharToBinary(buffer.GetBuffer()[i]));
	}
}

void Stego::CreateBinaryList(std::string buffer)
{
	// for every element inside the text buffer
	for (int i = 0; i < buffer.size(); i++)
	{
		// Covert it to binary and add to list
		binaryList.push_back(CharToBinary(buffer[i]));
	}
}

void Stego::BitNumber()
{
	bmp.GetFileHeader()->SetFileHeaderElement((unsigned char)binaryList.size() * 8, 6);
}

void Stego::CreatePixelListCopy()
{
	// Set up a 2D vector and initialise it to pixelList
	pixelList = std::vector<std::vector<RGB>>(bmp.GetHeight(), std::vector<RGB>(bmp.GetWidth()));

	//for each row
	for(int i = 0; i < bmp.GetHeight(); i++)
	{
		// for each element in a column
		for(int j = 0; j < bmp.GetWidth(); j++)
		{
			pixelList[i][j].SetRed(*bmp.GetPixelContainer()->GetRed(j));

			pixelList[i][j].SetGreen(*bmp.GetPixelContainer()->GetGreen(j));

			pixelList[i][j].SetBlue(*bmp.GetPixelContainer()->GetBlue(j));
		}
	}
}

void Stego::LSB()
{
	int k = 0;

	// For each character
	for(int i = 0; i < binaryList.size(); i++)
	{
		//Step through that characters binary representation, bit by bit
		for(int j = 0; j < binaryList[i].size(); j++)
		{
			// If the value ends in an odd number, the LSB has got to be 1.

			// If the value ends in an even number, the LSB has got be 0.

			// Check this against the binary value that we want to embed.  
			// If the pixel value ends in an odd number AND the binary entry is 0, enter condition
			if((pixelList[0][k].GetRed() % 2) == 1 && (binaryList[i][j] % 2) != 1)
			{
				unsigned char tempRED = pixelList[i][j].GetRed();
			
				//bitwise XOR - swap the value if both are equal (LSB switches from 1 to 0)
				pixelList[0][k].SetRed(tempRED ^= 1);

			}
			
			// If the pixel value ends in an even number AND the binary entry is 1, enter condition
			else if((pixelList[0][k].GetRed() % 2) == 0 && (binaryList[i][j] % 2) != 0)
			{
				unsigned char tempRED = pixelList[i][j].GetRed();

				//bitwise XOR - swap the value if both are equal (LSB switches from 1 to 0)
				pixelList[0][k].SetRed(tempRED ^= 1);
			}
			
			k++;
		}
	}
}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	int k = 0;

	bool firstIteration = true;

	for(int i = 0; i < bmp->GetHeight(); i++)
	{
		for(int j = 0; j < bmp->GetWidth(); j++)
		{
			if(firstIteration)
			{


				firstIteration = false;
			}

			pixelContainer.SetRed(pixelList[i][j].GetRed(), k);

			pixelContainer.SetGreen(pixelList[i][j].GetGreen(), k);

			pixelContainer.SetBlue(pixelList[i][j].GetBlue(), k);

			k++;
		}
		
	}

	GenerateImageData(bmp, pixelContainer, newFileName);

	fclose(bmp->GetFileObject()->GetFile());
}





void Stego::DistanceToOrigin(RGB& pixel, int modulusValue, unsigned long bit)
{
	int distance = RoundToInt(FindLength(pixel));

	int remainder = FindModulus(distance, modulusValue);

	std::pair<int, Direction> moveData = DistanceToSafeRemainder(remainder, DetermineSegment(remainder, modulusValue), bit, modulusValue);

	int newDistance = ModifyDistance(moveData, distance);

	Vec3f normalisedDistance = NormaliseDistance(distance, pixel);

	Vec3f scaledVector = ScaleVector(normalisedDistance, newDistance);

	RGB updatedRGB(scaledVector);

	pixel = RGB(updatedRGB);
}

std::pair<int, Direction> Stego::DistanceToSafeRemainder(int originalRemainder, int segment, unsigned long bitValue, int mod)
{		
	int half = mod / 2;
	int quarter = half / 2;
	int threeQuarter = half + quarter;

	if(segment == 0 && bitValue == 0)
	{
		if(originalRemainder < (quarter - 1)) //10
		{
			return std::make_pair<int, Direction>(std::abs((quarter - 1) - originalRemainder), Direction::LARGER); // 10
		}
		else if(originalRemainder > (quarter + 1)) // 12
		{
			return std::make_pair<int, Direction>(std::abs(originalRemainder - (quarter + 1)), Direction::SMALLER); // 12
		}
		else return std::make_pair<int, Direction>(0, Direction::STAY);
	}
	else if(segment == 1 && bitValue == 1)
	{
		if(originalRemainder < (threeQuarter - 1)) // 30
		{
			return std::make_pair<int, Direction>(std::abs((threeQuarter - 1) - originalRemainder), Direction::LARGER); // 30
		}
		else if(originalRemainder > (threeQuarter + 1)) // 32
		{
			return std::make_pair<int, Direction>(std::abs(originalRemainder - (threeQuarter + 1)), Direction::SMALLER); // 32
		}
		else return std::make_pair<int, Direction>(0, Direction::STAY);
	}
	else if(segment == 0 && bitValue == 1)
	{
		if(originalRemainder <= (quarter)) // 11
		{
			// Move remainder down past 0 to 32

			int a = std::abs(0 - originalRemainder);
			int b = std::abs(mod - threeQuarter); // 42 - 32
			int result = a + b;

			return std::make_pair<int, Direction>((int)result, Direction::SMALLER);

		}
		else if(originalRemainder >= (quarter + 1)) // 12
		{
			// Move remainder up to 30
						
			return std::make_pair<int, Direction>(std::abs((threeQuarter - 1) - originalRemainder), Direction::LARGER); //30
		}
	}
	else if(segment == 1 && bitValue == 0)
	{
		if(originalRemainder <= threeQuarter) // 31
		{
			// Move remainder down to 12

			return std::make_pair<int, Direction>(std::abs((quarter + 1) - originalRemainder), Direction::SMALLER); // 12
		}
		else if(originalRemainder >= (threeQuarter + 1)) // 32
		{
			// Move remainder up past 42 to 10
			int a = std::abs(originalRemainder - mod); //42
			int b = std::abs(0 - (quarter - 1)); // 10
			int result = a + b;

			return std::make_pair<int, Direction>((int)result, Direction::LARGER);
		}
	}
	else return std::make_pair<int, Direction>(0, Direction::UNDEFINED);
}

int Stego::ModifyDistance(std::pair<int, Direction> value, int distance)
{
	if(value.second == Direction::LARGER)
		return distance + value.first;
	else if(value.second == Direction::SMALLER)
		return distance - value.first;
	else return distance;
}

Vec3f Stego::NormaliseDistance(int distance, RGB value)
{
	return Vec3f(value / distance);
}

Vec3f Stego::ScaleVector(Vec3f normalised, int newDistance)
{
	return Vec3f(normalised.GetValues() * newDistance);
}





uint32_t Stego::PackData(uint8_t pixelsToRead, uint8_t modValue)
{
	return (pixelsToRead << 8) | modValue;
}

#pragma endregion