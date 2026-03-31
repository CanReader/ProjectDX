#include "ImageLoader.h"
#include <wrl/client.h>
#include <wincodec.h>

bool ImageLoader::LoadFromFile(const wchar_t* path, ImageData& data)
{
    using Microsoft::WRL::ComPtr;
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);

    ComPtr<IWICImagingFactory> factory;

    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&factory));

    if (FAILED(hr))
        return false;

    ComPtr<IWICBitmapDecoder> decoder;
    hr = factory->CreateDecoderFromFilename(path,nullptr,GENERIC_READ,WICDecodeMetadataCacheOnLoad,&decoder);

    if (FAILED(hr))
        return false;

    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0,&frame);
    
    if (FAILED(hr))
        return false;

    ComPtr<IWICFormatConverter> converter;
    factory->CreateFormatConverter(&converter);
    converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA,WICBitmapDitherTypeNone,nullptr,0.0f,WICBitmapPaletteTypeCustom);

    converter->GetSize(&data.width,&data.height);
    data.stride = data.width * 4; 

    UINT bufferSize = data.stride * data.height;
    data.pixels.resize(bufferSize);
    
    hr = converter->CopyPixels(nullptr,data.stride,bufferSize,data.pixels.data());

    return SUCCEEDED(hr);
}
