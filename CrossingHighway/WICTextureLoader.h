#pragma once
#include <d3d11.h>

namespace DirectX {
    HRESULT CreateWICTextureFromFile(
        ID3D11Device* device,
        const wchar_t* fileName,
        ID3D11Resource** texture,
        ID3D11ShaderResourceView** textureView);
}
