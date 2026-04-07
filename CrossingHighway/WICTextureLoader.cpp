#include "WICTextureLoader.h"
#include <wincodec.h>
#include <wrl/client.h>
#include <memory>

#pragma comment(lib, "windowscodecs.lib")

using Microsoft::WRL::ComPtr;

namespace DirectX {

HRESULT CreateWICTextureFromFile(
    ID3D11Device* device,
    const wchar_t* fileName,
    ID3D11Resource** texture,
    ID3D11ShaderResourceView** textureView)
{
    if (!device || !fileName) return E_INVALIDARG;
    if (!texture && !textureView) return E_INVALIDARG;

    ComPtr<IWICImagingFactory> factory;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                  IID_PPV_ARGS(&factory));
    if (FAILED(hr)) return hr;

    ComPtr<IWICBitmapDecoder> decoder;
    hr = factory->CreateDecoderFromFilename(fileName, nullptr, GENERIC_READ,
                                             WICDecodeMetadataCacheOnLoad, &decoder);
    if (FAILED(hr)) return hr;

    ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, &frame);
    if (FAILED(hr)) return hr;

    UINT width, height;
    hr = frame->GetSize(&width, &height);
    if (FAILED(hr)) return hr;

    ComPtr<IWICFormatConverter> converter;
    hr = factory->CreateFormatConverter(&converter);
    if (FAILED(hr)) return hr;

    hr = converter->Initialize(frame.Get(), GUID_WICPixelFormat32bppRGBA,
                                WICBitmapDitherTypeNone, nullptr, 0.0,
                                WICBitmapPaletteTypeCustom);
    if (FAILED(hr)) return hr;

    UINT rowPitch = width * 4;
    UINT imageSize = rowPitch * height;
    std::unique_ptr<uint8_t[]> pixels(new uint8_t[imageSize]);
    hr = converter->CopyPixels(nullptr, rowPitch, imageSize, pixels.get());
    if (FAILED(hr)) return hr;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = pixels.get();
    initData.SysMemPitch = rowPitch;

    ComPtr<ID3D11Texture2D> tex;
    hr = device->CreateTexture2D(&desc, &initData, &tex);
    if (FAILED(hr)) return hr;

    if (texture) {
        *texture = tex.Get();
        (*texture)->AddRef();
    }

    if (textureView) {
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = desc.Format;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = 1;
        hr = device->CreateShaderResourceView(tex.Get(), &srvDesc, textureView);
    }

    return hr;
}

} // namespace DirectX
