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
	uint32_t offset = 0;
	writeDirectory(icon16, header, file, offset);
	////// 32 X 32
	offset += icon16.pixels.size() + sizeof(BITMAPINFOHEADER);
	writeDirectory(icon32, header, file, offset);
	////// 64 X 64
	offset += icon32.pixels.size() + sizeof(BITMAPINFOHEADER);
	writeDirectory(icon64, header, file, offset);
	////// 128 X 128
	offset += icon64.pixels.size() + sizeof(BITMAPINFOHEADER);
	writeDirectory(icon128, header, file, offset);
	////// 256 X 256
	offset += icon128.pixels.size() + sizeof(BITMAPINFOHEADER);
	writeDirectory(icon256, header, file, offset);


	//



	////IMAGE and INFO
	//BITMAPINFOHEADER
	writeBITMAPINFO(icon16, file);
	writeBITMAPINFO(icon32, file);
	writeBITMAPINFO(icon64, file);
	writeBITMAPINFO(icon128, file);
	writeBITMAPINFO(icon256, file);


	if (!file) {
		return false;
	}

	return true;
}



void ICOEncoder::writeDirectory(const Image& icon, ICOHeader header, std::ofstream& file, uint32_t offset) {

	ICODirectory	directory{};

	directory.width = (icon.width == 256) ? 0 : icon.width;
	directory.height = (icon.height == 256) ? 0 : icon.height;
	directory.colorCount = static_cast<uint8_t>(0);
	directory.reserved = static_cast<uint8_t>(0);

	directory.plane = static_cast<uint16_t>(1);
	directory.bitCount = static_cast<uint16_t>(32);


	uint32_t pixelBytes = icon.width * icon.height * 4;
	uint32_t maskBytes = 0;
	directory.byteSize = static_cast<uint32_t>(sizeof(BITMAPINFOHEADER) + pixelBytes + maskBytes);
	//Offsett for 2nd image - sizeof(ICOHeader) + (sizeof(ICODirectory) * amount of images) + (bitmaninfoheader * 1) + size of 1st
	directory.offset = static_cast<uint32_t>(sizeof(ICOHeader) + (sizeof(ICODirectory) * header.count) + offset);

	file.write(reinterpret_cast<const char*>(&directory), sizeof(directory));
}


void ICOEncoder::writeBITMAPINFO(const Image& icon, std::ofstream& file) {

	BITMAPINFOHEADER bitmapHeader{}; 

	bitmapHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapHeader.biWidth = icon.width;
	bitmapHeader.biHeight = icon.height * 2;
	bitmapHeader.biPlanes = 1;
	bitmapHeader.biBitCount = 32;
	bitmapHeader.biCompression = 0;
	bitmapHeader.biSizeImage = static_cast<uint32_t>(icon.pixels.size());
	bitmapHeader.biXPelsPerMeter = 0;
	bitmapHeader.biYPelsPerMeter = 0;
	bitmapHeader.biClrUsed = 0;
	bitmapHeader.biClrImportant = 0;

	file.write(reinterpret_cast<const char*>(&bitmapHeader), sizeof(bitmapHeader));

	//Flip Image Right side up. (Otherwise image is upsidedown). 

	uint32_t byteWidth = icon.width * 4; // Pixel Width Count * 4 bytes

	for (int y = icon.height - 1; y >= 0; y--) { //Start at the bottom row and work up

		const uint8_t* row = icon.pixels.data() + (y * byteWidth); //Get Row data

		file.write(reinterpret_cast<const char*>(row), byteWidth); //Insert 

	}
}