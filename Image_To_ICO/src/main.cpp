#include "Converter.h"
#include "Utilities.h"


#include "pch.h"

int main() {
	//Setting up WIC
	HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	if (FAILED(hr)) {
		return -1;
	}

	Converter c;
	Image img = c.loadImageFile("C:\\Users\\farha\\Downloads\\test.jpg");

	ICO_LOG(img.width);
	ICO_LOG(img.height);
	ICO_LOG(img.pixels.size());


	ICO_LOG("===============================================================");


	Image croped = c.crop(img, 100, 100, 100, 100);

	ICO_LOG(croped.width);
	ICO_LOG(croped.height);
	ICO_LOG(croped.pixels.size());

	ICO_LOG("===============================================================");

	Image nearest = c.resize(croped, 32, 32, ResizeAlgorithm::Nearest);

	ICO_LOG(nearest.width);
	ICO_LOG(nearest.height);
	ICO_LOG(nearest.pixels.size());

	c.save(nearest, "work32.ico");

	
}