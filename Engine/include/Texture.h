#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d11.h>
#include <wrl/client.h>

class Texture
{
public:
	bool Load(ID3D11Device* dev, const wchar_t* path);
	void Bind(ID3D11DeviceContext* context, int slot = 0);
	
	int GetWidth() { return width; }
	int GetHeight() { return height; }
	
private:
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> sampler;

	int width = 0;
	int height = 0;
};

#endif