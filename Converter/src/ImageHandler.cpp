#include "ImageHandler.h"
#include "pch.h"
#include "Utilities.h"

#include <wincodec.h>
#include <comdef.h>


Image ImageHandler::loadImageFile(const std::string& file)
{

    HRESULT hr = S_OK;

    //Create WIC Factory
    IWICImagingFactory* factory = nullptr;

    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pFrame = nullptr;
    IWICFormatConverter* converter = nullptr;

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&factory)
    );

    std::wstring wFile(file.begin(), file.end());




    hr = factory->CreateDecoderFromFilename(
        wFile.c_str(),                      // Image to be decoded
        nullptr,                            // Do not prefer a particular vendor
        GENERIC_READ,                       // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,     // Cache metadata when needed
        &pDecoder                           // Pointer to the decoder
    );

    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    UINT width = 0;
    UINT height = 0;
    pFrame->GetSize(&width, &height);


    hr = factory->CreateFormatConverter(&converter);

    if (SUCCEEDED(hr))
    {
        hr = converter->Initialize(
            pFrame,                          // Input source to convert
            GUID_WICPixelFormat32bppBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            nullptr,                         // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    Image image_;
    image_.width = width;
    image_.height = height;
    image_.pixels.resize(width * height * 4); // BGRA  each pixel has 4 bytes of Blue Green Red Alpha

    converter->CopyPixels(
        nullptr,
        width * 4,
        (UINT)image_.pixels.size(),
        image_.pixels.data()
    );


    // Release in backwards order
    converter->Release();
    pFrame->Release();
    pDecoder->Release();
    factory->Release();

	return image_;
}
