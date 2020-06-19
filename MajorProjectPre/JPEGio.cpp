#include "JPEGio.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#pragma region Constructors

JPEGio::JPEGio() : file(nullptr), imageData(nullptr) {}

JPEGio::JPEGio(FileLoader* file) : file(file), imageData(nullptr)
{
	ReadPixels();
}

JPEGio::JPEGio(BMP* bmp, int compressionLevel) : file(nullptr), imageData(nullptr)
{
	ReadPixels();

	BMPtoJPEG(bmp, compressionLevel);
}

JPEGio::JPEGio(BMP bmp, int compressionLevel)
{
	file = bmp.GetFileObject();

	file->SetName(bmp.GetFileObject()->GetFileName());

	fileName = bmp.GetFileObject()->GetFileName();

	ReadPixels();

	BMPtoJPEG(&bmp, compressionLevel);
}

#pragma endregion

#pragma region Properties

std::pair<unsigned char*, Vec3i>* JPEGio::GetImageData() { return imageData; }

const char* JPEGio::GetFileName() { return fileName; }

#pragma endregion

#pragma region Methods

void JPEGio::ReadPixels()
{
	int width, height, channels;

	// do NOT vertically flip the image (keep it in the same orientation that the bmp was created, bottom to top)
	stbi_set_flip_vertically_on_load(false);

	unsigned char* arr = stbi_load(this->file->GetFileName(), &width, &height, &channels, STBI_rgb);
	Vec3i dimensions = {width, height, channels};

	this->imageData = new std::pair<unsigned char*, Vec3i>(arr, dimensions);
}

PixelContainer JPEGio::CopyPixelsToContainer(std::pair<unsigned char*, Vec3i> pixelArray)
{
	int width = pixelArray.second.GetX();
	int height = pixelArray.second.GetY();
	int channels = pixelArray.second.GetZ();

	int size = width * height * channels;

	PixelContainer pixelList(size, true);

	pixelList.SetArray(pixelArray.first);

	return pixelList;
}

void JPEGio::WriteJPEG(const char* name, int width, int height, int channels, PixelContainer* pixels, int quality)
{
	unsigned char* pixelData = new unsigned char[width * height * channels];

	int k = 0;
	int l = 0;

	for (int i = width * height; i != 0; --i)
	{
		pixelData[k] = *pixels->GetRed(l);
		pixelData[k + 1] = *pixels->GetGreen(l);
		pixelData[k + 2] = *pixels->GetBlue(l);

		l++;
		k += 3;
	}

	stbi_write_jpg(name, width, height, channels, pixelData, quality);

	delete[] pixelData;
}

void JPEGio::BMPtoJPEG(BMP* bmp, int compressionLevel)
{
	std::string f = ChangeExtension(bmp->GetFileHeader()->GetFileName(), "jpg"); // test this
	
	const char* c = static_cast<const char*>(f.c_str());

	fileName = c;

	WriteJPEG(fileName, bmp->GetWidth(), bmp->GetHeight(), bmp->GetColourSpace(), bmp->GetPixelContainer(), compressionLevel);

	imageData->second.SetX(bmp->GetWidth());

	imageData->second = Vec3i(bmp->GetWidth(), bmp->GetHeight(), bmp->GetColourSpace());
}

std::string JPEGio::ChangeExtension(const char* fileName, const char* newExtension)
{
	std::string fileNameString = fileName;

	int offset = fileNameString.find('.') + 1;
	int end = fileNameString.capacity();

	int extensionLength = end - offset;

	fileNameString.replace(offset, extensionLength, newExtension);

	return std::filesystem::path(fileNameString).filename().string();
}

#pragma endregion
