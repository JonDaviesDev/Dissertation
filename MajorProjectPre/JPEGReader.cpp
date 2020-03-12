#include "JPEGReader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma region Constructors

JPEGReader::JPEGReader(FileLoader* file) : file(file), imageData(nullptr)
{
	ReadPixels();
}

#pragma endregion

#pragma region Properties

std::pair<unsigned char*, Vec3i>* JPEGReader::GetImageData() { return imageData; }

#pragma endregion

#pragma region Methods

void JPEGReader::ReadPixels()
{
	int width, height, channels;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* arr = stbi_load(this->file->GetFileName(), &width, &height, &channels, STBI_rgb);
	Vec3i dimensions = {width, height, channels};

	this->imageData = new std::pair<unsigned char*, Vec3i>(arr, dimensions);
}

PixelContainer JPEGReader::CopyPixelsToContainer(std::pair<unsigned char*, Vec3i> pixelArray)
{
	int width = pixelArray.second.GetX();
	int height = pixelArray.second.GetY();
	int channels = pixelArray.second.GetZ();

	int size = width * height * channels;

	PixelContainer pixelList(size, true);

	pixelList.SetArray(pixelArray.first);

	return pixelList;
}

#pragma endregion
