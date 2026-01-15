#include "Mesh.h"

bool Mesh::Initialize(ID3D11Device* device)
{
    if (meshData.GetVertices().empty() || meshData.GetIndices().empty())
        return false;

    vertexBuffer = std::make_unique<Buffer>(BufferType::Vertex);
    if (!vertexBuffer->Create(device,
        sizeof(DirectX::XMFLOAT3),
        meshData.GetVertCount(),
        meshData.GetVertices().data()))
        return false;

    indexBuffer = std::make_unique<Buffer>(BufferType::Index);
    if (!indexBuffer->Create(device,
        sizeof(uint32_t),
        meshData.GetIndexCount(),
        meshData.GetIndices().data()))
        return false;

    return true;
}

void Mesh::Render(ID3D11DeviceContext* context)
{
    if (vertexBuffer && indexBuffer)
    {
        vertexBuffer->Bind(context);
        indexBuffer->Bind(context);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        context->DrawIndexed(indexBuffer->GetCount(),0,0);
    }
}
