#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <wrl/client.h>
#include <D3D11.h>

enum class BufferType {
	Vertex,
	Index,
	Constant,
	Unknown
};

class Buffer
{
public:
	Buffer(BufferType type) : type(type) {}
	~Buffer() = default;

	bool Create(ID3D11Device* device,
		UINT elementSize,
		UINT elementCount,
		const void* initData = nullptr,
		bool dynamic = false,
		bool cpuAccess = false);

	void Bind(ID3D11DeviceContext* context, UINT slot = 0) const;
	void Update(ID3D11DeviceContext* context, const void* data, size_t size);

	const size_t& GetCount() const { return count; }
	ID3D11Buffer* Get() const { return buffer.Get(); }
	BufferType GetType() const { return type; }

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;


	BufferType type = BufferType::Unknown;

	UINT stride = 0;
	UINT count = 0;
	bool dynamic = 0;
};

#endif