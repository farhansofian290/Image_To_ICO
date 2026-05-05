#include "pch.h"
#include "Converter.h"
#include "ImageHandler.h"

Image Converter::loadImageFile(const std::string& file)
{
    return ImageHandler::loadImageFile(file);
}