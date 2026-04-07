////////////////////////////////////////////////////////////////////////////////
// Filename: textureclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "textureclass.h"


TextureClass::TextureClass()
{
	m_texture = 0;
}


TextureClass::TextureClass(const TextureClass& other)
{
}


TextureClass::~TextureClass()
{
}


bool TextureClass::Initialize(ID3D11Device* device, const WCHAR* filename)
{
	HRESULT result;


	// Check file extension to use appropriate loader.
	std::wstring fn(filename);
	if (fn.size() >= 4 && fn.substr(fn.size() - 4) == L".dds")
	{
		result = DirectX::CreateDDSTextureFromFile(device, filename, nullptr, &m_texture);
	}
	else
	{
		result = DirectX::CreateWICTextureFromFile(device, filename, nullptr, &m_texture);
	}
	if(FAILED(result))
	{
		char buf[256];
		sprintf_s(buf, "TextureClass: Failed to load texture, HRESULT=0x%08X\n", (unsigned int)result);
		OutputDebugStringA(buf);
		OutputDebugStringW(L"  File: ");
		OutputDebugStringW(filename);
		OutputDebugStringW(L"\n");
		return false;
	}

	return true;
}


void TextureClass::Shutdown()
{
	// Release the texture resource.
	if(m_texture)
	{
		m_texture->Release();
		m_texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* TextureClass::GetTexture()
{
	return m_texture;
}