#include "Object.h"
#include "Mesh.h"
#include "Shader.h"

Object::Object(std::string name, Mesh* mesh) : name(name),mesh(mesh), shader(new Shader())  {

}

Object::~Object()
{

}

bool Object::Initialize(ID3D11Device* device) {
	if (shader) {
		shader->CreateVertexShader(device,L"BasicShader.hlsl");
		shader->CreatePixelShader(device,L"BasicShader.hlsl");
	}
	else
		return false;

	if (mesh)
		return mesh->Initialize(device);
	else
		return false;
}

void Object::Render(ID3D11DeviceContext* context)  {
	if (!isVisible || !mesh || !shader)
		return;

	shader->Bind(context);
	mesh->Render(context);
}