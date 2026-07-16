#pragma once

#include "Image.h"
#include "ImageAlgorithms.h"


class ImageProcessor {
public:
	static Image crop(const Image& main, size_t startX, size_t startY, size_t xSize, size_t ySize);

	static Image resize(const Image& image, size_t newWidth, size_t newHeight, ResizeAlgorithm algo);

	static Image nearestNeighbor(const Image& image, size_t newWidth, size_t newHeight);
};