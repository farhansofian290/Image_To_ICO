#include "ICOEncoder.h"
#include <fstream>

bool ICOEncoder::save(const Image& image, const std::string& filename)
{

	//https://docs.fileformat.com/image/ico/

	std::ofstream file(filename, std::ios::binary);
	if (!file) {
		return false;
	}

	ICOHeader header{};
	ICODirectory	directory{};
	BITMAPINFOHEADER	bitmapHeader{};

	//Make it an ICO format
	header.reserved = 0;
	header.type = 1;
	header.count = 1;

	file.write(reinterpret_cast<const char*>(&header), sizeof(header));

	/*
	uint8_t width;
	uint8_t height;
	uint8_t colorCount;
	uint8_t reserved;

	uint16_t plane;
	uint16_t bitCount;

	uint32_t byteSize;
	uint32_t offset
	*/

	directory.width = (image.width == 256) ? 0 : image.width;
	directory.height = (image.height == 256) ? 0 : image.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes = image.width * image.height * 4;
	uint32_t maskBytes = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes + maskBytes);
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + sizeof(ICODirectory));

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	/*
	uint32_t biSize;
	int32_t  biWidth;
	int32_t  biHeight;
	uint16_t  biPlanes;
	uint16_t  biBitCount;
	uint32_t biCompression;
	uint32_t biSizeImage;
	int32_t  biXPelsPerMeter;
	int32_t  biYPelsPerMeter;
	uint32_t biClrUsed;
	uint32_t biClrImportant;
	*/

	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = image.width;
	bitmapHeader.biHeight = image.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));



	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth = image.width * 4; // Pixel Width Count * 4 bytes

	for (int y = image.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = image.pixels.data() + (y * byteWidth); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth); //Insert 

	}


	//file.write(reinterpret_cast<const char*>(image.pixels.data()), image.pixels.size());

	if (!file) {
		return false;
	}

	return true;
}
