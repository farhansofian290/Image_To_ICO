#include "Converter.h"


#include "pch.h"

int main() {
	//Setting up WIC
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (FAILED(hr)) {
		return -1;
	}

	Converter c;
	Image img = c.loadImageFile("test.png");

	std::cout << img.width << std::endl;
	std::cout << img.height << std::endl;
	std::cout << img.pixels.size() << std::endl;


}