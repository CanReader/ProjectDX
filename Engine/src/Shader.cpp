#include "Shader.h"
#include "Logger.h"

Shader::Shader(){}
bool Shader::CreateVertexShader(ID3D11Device* device, const std::wstring& path)
{
    Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;

    if (!CompileShaderFromFile(path, "VSMain", "vs_5_0", vsBlob))
        return false;

    HRESULT hr = device->CreateVertexShader(
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        nullptr,
        &vertexShader);

    if (FAILED(hr))
        return false;

    D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[1]
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA,0}
    };

    hr = device->CreateInputLayout(layout,
        1,
        vsBlob->GetBufferPointer(),
        vsBlob->GetBufferSize(),
        &shaderLayout);

    delete[] layout;

    return SUCCEEDED(hr);
}

bool Shader::CreatePixelShader(ID3D11Device* device, const std::wstring& path)
{
    Microsoft::WRL::ComPtr<ID3DBlob> psBlob;

    if (!CompileShaderFromFile(path, "PSMain", "ps_5_0", psBlob))
        return false;

    HRESULT hr = device->CreatePixelShader(
        psBlob->GetBufferPointer(),
        psBlob->GetBufferSize(),
        nullptr,
        &pixelShader);

    return SUCCEEDED(hr);
}

void Shader::Bind(ID3D11DeviceContext* context)
{
    if (vertexShader)
    {
        context->IASetInputLayout(shaderLayout.Get());
        context->VSSetShader(vertexShader.Get(),nullptr,0);
    }
    if (pixelShader) {
        context->PSSetShader(pixelShader.Get(), nullptr, 0);
    }
}

bool Shader::CompileShaderFromFile(const std::wstring& path, const std::string& entryPoint, const std::string& shaderModel, Microsoft::WRL::ComPtr<ID3DBlob>& out)
{
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob = nullptr;

    HRESULT hr = D3DCompileFromFile(
        path.c_str(),
        nullptr, nullptr,
        entryPoint.c_str(),
        shaderModel.c_str(),
        D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION,
        0,
        &out,
        &errorBlob
        );

    if (FAILED(hr))
    {
        if (errorBlob) {
            DX_ERROR("Shader compilation error ({}) : {}", entryPoint, (char*)errorBlob->GetBufferPointer());
        }
        else {
            DX_ERROR("Failed to compile shader: unknown error");
        }
    }

    return SUCCEEDED(hr);
}
