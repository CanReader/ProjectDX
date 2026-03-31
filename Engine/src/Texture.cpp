#include "Texture.h"
#include "ImageLoader.h"


bool Texture::Load(ID3D11Device* dev, const wchar_t* path)
{
    ImageData data;

    if (!ImageLoader::LoadFromFile(path, data))
        return false;

    width = (int)data.width;
    height = (int)data.height;

    D3D11_TEXTURE2D_DESC desc = {};
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    
    D3D11_SUBRESOURCE_DATA init = {};
    init.pSysMem = data.pixels.data();
    init.SysMemPitch = data.stride;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;
    HRESULT hr = dev->CreateTexture2D(&desc,&init,&texture);

    if (FAILED(hr))
        return false;

    hr = dev->CreateShaderResourceView(texture.Get(),nullptr,&srv);
    if (FAILED(hr))
        return false;

    D3D11_SAMPLER_DESC sdesc = {};
    sdesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

    hr = dev->CreateSamplerState(&sdesc,&sampler);
    if (FAILED(hr))
        return false;

    return true;
}

void Texture::Bind(ID3D11DeviceContext* con, int slot) {
    if (srv && sampler) {
        con->PSSetShaderResources(slot,1,srv.GetAddressOf());
        con->PSSetSamplers(slot,1,sampler.GetAddressOf());
    }
}
