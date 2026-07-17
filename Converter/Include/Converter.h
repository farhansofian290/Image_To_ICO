#pragma once

#include "string"
#include "Image.h"
#include "ImageAlgorithms.h"

class Converter {
public:
    Image loadImageFile(const std::string& file);

    Image crop(const Image& main, size_t startX, size_t startY, size_t xSize, size_t ySize);

    Image resize(const Image& image, size_t newWidth, size_t newHeight, ResizeAlgorithm algo);

    bool save(const Image& image, const std::string& filename);
};