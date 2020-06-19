#include "Stego.h"

#pragma region Constructors

Stego::Stego(){}

Stego::Stego(FileLoader* coverBMP, FileLoader* textFile, const char* newFileName, Method method, int modValue)
	: bmp(coverBMP), text(textFile), stegoFileName(newFileName)
{
	informationContainer = PackData(text.GetBuffer().size() * 8, modValue);

	int k = 0;

	CreatePixelListCopy();

	CreateBinaryList(text);

	BitNumber();

	if (method == Method::DTO)
	{
		Timer timer("DTO");

		for (int i = 0; i < binaryList.size(); i++)
		{
			for (int j = 0; j < binaryList[i].size(); j++)
			{
				DistanceToOrigin(pixelList[0][k], modValue, binaryList[i][j]);

				k++;
			}
		}

		functionTime = timer.GetTime();
	}
	else if (method == Method::LSB)
	{
		LSB();
	}
	else
	{
		exit(-1);
	}
	
	ModifyBMP(&bmp, newFileName);
}

Stego::Stego(FileLoader* coverBMP, std::string* text, const char* newFileName, Method method, int modValue)
	: bmp(coverBMP), text(*text), stegoFileName(newFileName)
{
	informationContainer = PackData(this->text.GetBuffer().size() * 8, modValue);

	int k = 0;

	CreatePixelListCopy();

	CreateBinaryList(*text);

	BitNumber();

	if (method == Method::DTO)
	{
		Timer timer("DTO");

		for (int i = 0; i < binaryList.size(); i++)
		{
			for (int j = 0; j < binaryList[i].size(); j++)
			{
				DistanceToOrigin(pixelList[0][k], modValue, binaryList[i][j]);

				k++;
			}
		}

		functionTime = timer.GetTime();
	}
	else if (method == Method::LSB)
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

float Stego::GetFunctionTime() { return functionTime; }

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
	Timer timer("LSB");

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

	functionTime = timer.GetTime();
}

void Stego::ModifyBMP(BMP* bmp, const char* newFileName)
{
	PixelContainer pixelContainer(bmp->GetWidth(), bmp->GetHeight());

	int k = 0;

	for(int i = 0; i < bmp->GetHeight(); i++)
	{
		for(int j = 0; j < bmp->GetWidth(); j++)
		{
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
	// Find the distance to the origin of the image (0, 0, 0)
	int distance = RoundToInt(FindLength(pixel));	

	// Find the remainder
	int remainder = FindModulus(distance, modulusValue);	

	// Find the number of values to move the remainder and a direction to move it in
	std::pair<int, Direction> moveData = DistanceToSafeRemainder(remainder, DetermineSegment(remainder, modulusValue), bit, modulusValue);

	// Find the new distance to origin
	int newDistance = ModifyDistance(moveData, distance);

	// Normalise the original pixel
	Vec3f normalisedDistance = NormaliseDistance(distance, pixel);

	// Scale the normalised vector using the new distance
	Vec3f scaledVector = ScaleVector(normalisedDistance, newDistance);

	// Update the pixel
	RGB updatedRGB(scaledVector);
	pixel = RGB(updatedRGB);
}

std::pair<int, Direction> Stego::DistanceToSafeRemainder(int originalRemainder, int segment, unsigned long bitValue, int mod)
{		
	// Initialisions
	int half = mod / 2;
	int quarter = half / 2;
	int threeQuarter = half + quarter;

	/* This function uses the first two conditions to see if the segment that the remainder sits in and the value of the next 
	   bit to be embedded match up.  If they do, then a simple calculation to see how far to move the remainder so that it 
	   sits in the centre of its alloted segment is done.  This data is return in as a pair.
	   
	   The third and forth conditions are run should the first two fail.  These check for remainders that need to be moved from
	   their current segment and into the other one.  If this needs to happen, a calculation that allows for the crossing of
	   boundries is done and this data is also stored in a pair object.
	   
	   The last condition returns a pair with default values for undefined behaviour.
	*/


	// If the remainder lies in segment 0 AND the next bit to be embedded is 0
	if(segment == 0 && bitValue == 0)	
	{
		// if the remainder sits in the lower quarter of its segment, it needs to be moved up to the centre of its segment
		if(originalRemainder < (quarter - 1))
		{
			return std::make_pair<int, Direction>(std::abs((quarter - 1) - originalRemainder), Direction::LARGER);
		}
		// if the remainder is in the higher section of its segment, it needs to be moved lower to the centre
		else if(originalRemainder > (quarter + 1))
		{
			return std::make_pair<int, Direction>(std::abs(originalRemainder - (quarter + 1)), Direction::SMALLER);
		}
		// if both of the above conditions are false, the remainder is already near the centre of its segment and can stay still
		else return std::make_pair<int, Direction>(0, Direction::STAY);
	}
	// If the remainder lies in segment 1 AND the next bit to be embedded is 1
	else if(segment == 1 && bitValue == 1)
	{
		// if the remainder sits in the lower portion of its segment, it needs to be moved up to the centre of its segment
		if(originalRemainder < (threeQuarter - 1))
		{
			return std::make_pair<int, Direction>(std::abs((threeQuarter - 1) - originalRemainder), Direction::LARGER);
		}
		// if the remainder sits in the higher quarter of its segment, it needs to be moved down to the centre of its segment
		else if(originalRemainder > (threeQuarter + 1))
		{
			return std::make_pair<int, Direction>(std::abs(originalRemainder - (threeQuarter + 1)), Direction::SMALLER);
		}
		// the remainder is in the right part of the segment and can stay where it is
		else return std::make_pair<int, Direction>(0, Direction::STAY);
	}
	// If the remainder lies in segment 0 AND the next bit to be embedded is 1
	else if(segment == 0 && bitValue == 1)
	{
		// For this section it is easier to think of the values on a number line

		// 0--------------------mod/2--------------------mod 


		// if the remainder is in the lower portion of the smaller segment (the one that represents 0)
		if(originalRemainder <= (quarter))
		{
			// Move remainder down past 0 to the centre of the larger segment (the one that represents 1)



			//		<------R							  movedR<----------
			//	       0-------|----|---------mod/2-------|----|-------mod 
			//                  safe					   safe



			int a = std::abs(0 - originalRemainder);
			int b = std::abs(mod - threeQuarter); // 42 - 32
			int result = a + b;

			return std::make_pair<int, Direction>((int)result, Direction::SMALLER);

		}
		// if the remainder is larger than the centre point of the smaller segment,
		// move the remainder up from the lower segment to the centre of the higher
		else if(originalRemainder >= (quarter + 1))
		{
			//		                     R--------------->movedR	
			//	       0-------|----|---------mod/2-------|----|-------mod 
			//                  safe					   safe
						
			return std::make_pair<int, Direction>(std::abs((threeQuarter - 1) - originalRemainder), Direction::LARGER); //30
		}
	}
	// If the remainder lies in segment 1 AND the next bit to be embedded is 0
	else if(segment == 1 && bitValue == 0)
	{
		// if the remainder lies below the centre of the higher segment, lower it down to the centre of the lower segment

			//				   movedR<----------------R
			//	       0-------|----|---------mod/2-------|----|-------mod 
			//                  safe					   safe

		if(originalRemainder <= threeQuarter) // 31
		{
			// Move remainder down to 12

			return std::make_pair<int, Direction>(std::abs((quarter + 1) - originalRemainder), Direction::SMALLER); // 12
		}

		// if the remainder lies above the centre of the higher segment, move it up past 0 to the centre of the lower segment

	//		 --------->movedR                              R------->
	//	       0-------|----|---------mod/2-------|----|-------mod 
	//                  safe					   safe

		else if(originalRemainder >= (threeQuarter + 1)) // 32
		{
			
			int a = std::abs(originalRemainder - mod); //42
			int b = std::abs(0 - (quarter - 1)); // 10
			int result = a + b;

			return std::make_pair<int, Direction>((int)result, Direction::LARGER);
		}
	}
	// This will return if an invalid segment/remainder is entered
	else return std::make_pair<int, Direction>(0, Direction::UNDEFINED);
}

int Stego::ModifyDistance(std::pair<int, Direction> value, int distance)
{
	// This uses the calculations made in the 'DistanceToSafeRemainder' function to simply move the value
	// of the remainder in the required direction for the required number of values
	if(value.second == Direction::LARGER)
		return distance + value.first;
	else if(value.second == Direction::SMALLER)
		return distance - value.first;
	else return distance;
}

Vec3f Stego::NormaliseDistance(int distance, RGB value)
{
	return Vec3f(value / distance); // overloaded '/' operator
}

Vec3f Stego::ScaleVector(Vec3f normalised, int newDistance)
{
	return Vec3f(normalised.GetValues() * newDistance); // overloaded '*' operator
}





uint32_t Stego::PackData(uint8_t pixelsToRead, uint8_t modValue)
{
	return (pixelsToRead << 8) | modValue;
}

#pragma endregion