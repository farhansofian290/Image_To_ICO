#include "pch.h"
#include "Converter.h"
#include "ImageHandler.h"
#include "ImageProcessor.h"

Image Converter::loadImageFile(const std::string& file)
{
    return ImageHandler::loadImageFile(file);

}

Image Converter::crop(const Image& main, size_t startX, size_t startY, size_t xSize, size_t ySize) {
    return ImageProcessor::crop(main, startX, startY, xSize, ySize);
}

Image Converter::resize(const Image& image, size_t newWidth, size_t newHeight, ResizeAlgorithm algo) {
    return ImageProcessor::resize(image, newWidth, newHeight, algo);
}