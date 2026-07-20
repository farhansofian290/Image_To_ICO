#pragma once


#include <cstdint>
#include "Image.h"
#include <string>


//https://docs.fileformat.com/image/ico/

struct ICOHeader
{
	uint16_t reserved;
	uint16_t type;
	uint16_t count;
};

struct ICODirectory
{
	uint8_t width;
	uint8_t height;
	uint8_t colorCount;
	uint8_t reserved;

	uint16_t plane;
	uint16_t bitCount;

	uint32_t byteSize;
	uint32_t offset;
};

//Image Data Start of the Actual Image data. Pixel data is after this 40 byte BITMAPINFOHEADER
struct BITMAPINFOHEADER { //Microsoft BITMAPINFOHEADER Structure
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
};

class ICOEncoder {
public:
	static bool save(const Image& image, const std::string& filename);

private:
	static void writeDirectory(const Image& icon, ICOHeader header, std::ofstream& file, uint32_t offset);
	static void writeBITMAPINFO(const Image& icon, std::ofstream& file);

};