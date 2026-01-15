#ifndef _MESH_H_
#define _MESH_H_

#include <DirectXMath.h>
#include <vector>
#include <D3D11.h>
#include <memory>
#include "Buffer.h"

class MeshData {
public:
	MeshData(std::initializer_list<DirectX::XMFLOAT3> verts, std::initializer_list<uint32_t> inds) :
		vertices(verts), indices(inds) {}

	void SetVertices(const std::vector<DirectX::XMFLOAT3>& verts) { vertices = verts; }
	const std::vector<DirectX::XMFLOAT3>& GetVertices() const { return vertices; }
	size_t GetVertCount() { return vertices.size(); }

	void SetIndices(const std::vector<uint32_t>& inds) { indices = inds; }
	const std::vector<uint32_t>& GetIndices() const { return indices; }
	size_t GetIndexCount() { return indices.size(); }

private:
	std::vector<DirectX::XMFLOAT3> vertices;
	std::vector<uint32_t> indices;
};

class Buffer;
class Mesh
{
public:
	Mesh() = default;
	Mesh(MeshData data) : meshData(data) {}
	Mesh(std::initializer_list<DirectX::XMFLOAT3> verts, std::initializer_list<uint32_t> inds) : meshData(verts,inds) {}
	virtual ~Mesh() = default;

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);

private:
	MeshData meshData;
	std::unique_ptr<Buffer> vertexBuffer;
	std::unique_ptr<Buffer> indexBuffer;
};

#endif