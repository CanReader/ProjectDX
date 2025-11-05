#ifndef  _SHADER_H_
#define _SHADER_H_

#include <string>
#include <wrl/client.h>
#include <d3d11.h>
#include <d3dcompiler.h>

class Shader
{
public:
	Shader();
	~Shader() = default;

	bool CreateVertexShader(ID3D11Device* device,
		const std::wstring& path);

	bool CreatePixelShader(ID3D11Device* device,
		const std::wstring& path);

	void Bind(ID3D11DeviceContext* context);
	
private:
	bool CompileShaderFromFile(
	const std::wstring& path,
	const std::string& entryPoint,
	const std::string& shaderModel,
	Microsoft::WRL::ComPtr<ID3DBlob>& out);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> shaderLayout;

};


#endif 