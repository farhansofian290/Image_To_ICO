#include "ICOEncoder.h"
#include <fstream>
#include "ImageProcessor.h"

bool ICOEncoder::save(const Image& image, const std::string& filename)
{




	Image icon16 = ImageProcessor::resize(image, 16, 16, ResizeAlgorithm::Nearest);
	Image icon32 = ImageProcessor::resize(image, 32, 32, ResizeAlgorithm::Nearest);
	Image icon64 = ImageProcessor::resize(image, 64, 64, ResizeAlgorithm::Nearest);
	Image icon128 = ImageProcessor::resize(image, 128, 128, ResizeAlgorithm::Nearest);
	Image icon256 = ImageProcessor::resize(image, 256, 256, ResizeAlgorithm::Nearest);


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
	header.count = 5;

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



	
	// DIRECTORIES

	////// 16 X 16
	directory.width = (icon16.width == 256) ? 0 : icon16.width;
	directory.height = (icon16.height == 256) ? 0 : icon16.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes16 = icon16.width * icon16.height * 4;
	uint32_t maskBytes16 = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes16 + maskBytes16);

	//Offsett for 1st image is ICOHEADER + (ICODIRECTORY * amount of images)
	//Offsett for 2nd image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images)
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count));

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	////// 32 X 32
	directory.width = (icon32.width == 256) ? 0 : icon32.width;
	directory.height = (icon32.height == 256) ? 0 : icon32.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes32 = icon32.width * icon32.height * 4;
	uint32_t maskBytes32 = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes32 + maskBytes32);
	//Offsett for 2nd image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images) + (bitmaninfoheader * 1) + size of 1st
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count) + (sizeof(BITMAPINFOHEADER) * 1) + pixelBytes16);

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	////// 64 X 64
	directory.width = (icon64.width == 256) ? 0 : icon64.width;
	directory.height = (icon64.height == 256) ? 0 : icon64.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes64 = icon64.width * icon64.height * 4;
	uint32_t maskBytes64 = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes64 + maskBytes64);

	//Offsett for 3rd image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images)  + (bitmaninfoheader * 2) + size of 1st + 2nd
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count) + (sizeof(BITMAPINFOHEADER) * 2) + pixelBytes16 + pixelBytes32);

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	////// 128 X 128
	directory.width = (icon128.width == 256) ? 0 : icon128.width;
	directory.height = (icon128.height == 256) ? 0 : icon128.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes128 = icon128.width * icon128.height * 4;
	uint32_t maskBytes128 = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes128 + maskBytes128);
	//Offsett for 4th image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images)  + (bitmaninfoheader * 3) + size of 1st + 2nd + 3rd
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count) + (sizeof(BITMAPINFOHEADER) * 3 ) + pixelBytes16 + pixelBytes32 + pixelBytes64);

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	////// 256 X 256
	directory.width = (icon256.width == 256) ? 0 : icon256.width;
	directory.height = (icon256.height == 256) ? 0 : icon256.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes256 = icon256.width * icon256.height * 4;
	uint32_t maskBytes256 = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes256 + maskBytes256);
	//Offsett for 5th image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images)  + (bitmaninfoheader * 4) + size of 1st + 2nd + 3rd + 4th
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count) + (sizeof(BITMAPINFOHEADER) * 4) + pixelBytes16 + pixelBytes32 + pixelBytes64 + pixelBytes128);

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));

	////IMAGE and INFO
	//BITMAPINFOHEADER
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

	//IMAGE ICON 16 x 16
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon16.width;
	bitmapHeader.biHeight = icon16.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes16);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth16 = icon16.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon16.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon16.pixels.data() + (y * byteWidth16); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth16); //Insert 

	}

	//IMAGE ICON 32 x 32
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon32.width;
	bitmapHeader.biHeight = icon32.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes32);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth32 = icon32.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon32.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon32.pixels.data() + (y * byteWidth32); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth32); //Insert 

	}

	//IMAGE ICON 64 x 64
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon64.width;
	bitmapHeader.biHeight = icon64.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes64);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth64 = icon64.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon64.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon64.pixels.data() + (y * byteWidth64); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth64); //Insert 

	}

	//IMAGE ICON 128 x 128
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon128.width;
	bitmapHeader.biHeight = icon128.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes128);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth128 = icon128.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon128.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon128.pixels.data() + (y * byteWidth128); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth128); //Insert 

	}

	//IMAGE ICON 256 x 256
	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon256.width;
	bitmapHeader.biHeight = icon256.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = (pixelBytes256);
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth256 = icon256.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon256.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon256.pixels.data() + (y * byteWidth256); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth256); //Insert 

	}





	if (!file) {
		return false;
	}

	return true;
}
