#include "Buffer.h"
#include "Logger.h"

bool Buffer::Create(ID3D11Device* device, UINT elementSize, UINT elementCount, const void* initData, bool dynamic, bool cpuAccess)
{
    this->stride = elementSize;
    this->count = elementCount;
    this->dynamic = dynamic;

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc,sizeof(D3D11_BUFFER_DESC));
    desc.ByteWidth = stride * count;
    desc.StructureByteStride = stride;

    switch(type) {
    case BufferType::Vertex: desc.BindFlags = D3D11_BIND_VERTEX_BUFFER; break;
    case BufferType::Index: desc.BindFlags = D3D11_BIND_INDEX_BUFFER; break;
    case BufferType::Constant: desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; break;
    default: return false;
    }

    if (dynamic) {
        desc.Usage = D3D11_USAGE_DYNAMIC;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    } else if (cpuAccess) {
        desc.Usage = D3D11_USAGE_STAGING;
        desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    }
    else {
        desc.Usage = D3D11_USAGE_DEFAULT;
    }

    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
    if (initData)
        data.pSysMem = initData;

    HRESULT hr = device->CreateBuffer(&desc,&data,&buffer);

    return SUCCEEDED(hr);
}

void Buffer::Bind(ID3D11DeviceContext* context, UINT slot) const
{
    switch (type) {
    case BufferType::Vertex:
        context->IASetVertexBuffers(slot,1,buffer.GetAddressOf(),&stride,&slot);
        break;
    case BufferType::Index:
        context->IASetIndexBuffer(buffer.Get(),DXGI_FORMAT_R32_UINT,0);
        break;
    case BufferType::Constant:
        context->VSSetConstantBuffers(slot,1,buffer.GetAddressOf());
        context->PSSetConstantBuffers(slot, 1, buffer.GetAddressOf());
        break;
    default:
        break;
    }
}

void Buffer::Update(ID3D11DeviceContext* context, const void* data, size_t size)
{
    if (dynamic) {
        D3D11_MAPPED_SUBRESOURCE map = {};
        HRESULT hr = context->Map(buffer.Get(),0,D3D11_MAP_WRITE_DISCARD,0,&map);
        if (SUCCEEDED(hr))
        {
            memcpy(map.pData,data,size);
            context->Unmap(buffer.Get(),0);
        }
        else {
            DX_ERROR("Failed to map dynamic buffer for update.");
        }
    }
    else {
        context->UpdateSubresource(buffer.Get(),0,nullptr,data,0,0);
    }
}
