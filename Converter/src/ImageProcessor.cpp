#include "ImageProcessor.h"

Image ImageProcessor::crop(const Image& main, size_t startX, size_t startY, size_t xSize, size_t ySize)
{

	//Create the new Image object
	Image finalImage;
	finalImage.width = xSize;
	finalImage.height = ySize;
	finalImage.pixels.resize(xSize * ySize * 4);


	for (size_t y = 0; y < ySize; y++) {
		for (size_t x = 0; x < xSize; x++) {
			size_t yIndex = startY + y;
			size_t xIndex = startX + x;

			size_t sourceIndex = (yIndex * main.width + xIndex) * 4;
			size_t finalIndex = (y * xSize + x) * 4;


			for (size_t bgra = 0; bgra < 4; bgra++) {
				finalImage.pixels[finalIndex + bgra] = main.pixels[sourceIndex + bgra];
			}




		}
	}




	return finalImage;
}

Image ImageProcessor::resize(const Image& image, size_t newWidth, size_t newHeight, ResizeAlgorithm algo)
{
	
	switch (algo) {
	case ResizeAlgorithm::Nearest:
		return nearestNeighbor(image, newWidth, newHeight);
	}

	return Image();
}

Image ImageProcessor::nearestNeighbor(const Image& image, size_t newWidth, size_t newHeight)
{
	Image result;
	result.width = newWidth;
	result.height = newHeight;
	result.pixels.resize(newWidth * newHeight * 4);

	float xScale = static_cast<float>(image.width) / newWidth;
	float yScale = static_cast<float>(image.height) / newHeight;

	for (size_t y = 0; y < newHeight; y++) {
		for (size_t x = 0; x < newWidth; x++) {

			size_t srcX = static_cast<size_t>(x * xScale); //Find nearest X
			size_t srcY = static_cast<size_t>(y * yScale); //Find nearest Y

			size_t sourceIndex = (srcY * image.width + srcX) * 4;
			size_t finalIndex = (y * newWidth + x) * 4;


			for (int bgra = 0; bgra < 4; bgra++) {
				result.pixels[finalIndex + bgra] = image.pixels[sourceIndex + bgra];
			}
		}
	}





	return result;
}
