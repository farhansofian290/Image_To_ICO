#pragma once

#include <string>
#include "Image.h"

class Converter {
public:
    Image loadImageFile(const std::string& file);
};