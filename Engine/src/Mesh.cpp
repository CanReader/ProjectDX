#include "Mesh.h"

bool Mesh::Initialize(ID3D11Device* device)
{
    if (meshData.GetVertices().empty())
        return false;

    vertexBuffer = std::make_unique<Buffer>(BufferType::Vertex);
    if (!vertexBuffer->Create(device,
        sizeof(DirectX::XMFLOAT3),
        meshData.GetVertCount(),
        meshData.GetVertices().data()))
        return false;

    return true;
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    if (vertexBuffer)
    {
        vertexBuffer->Bind(context);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->Draw(vertexBuffer->GetCount(),0);
    }
}
