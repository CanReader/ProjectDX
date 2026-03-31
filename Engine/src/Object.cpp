#include "Object.h"
#include "Mesh.h"
#include "Shader.h"

Object::Object(std::string name, Mesh* mesh) : name(name),mesh(mesh), shader(new Shader()), texture(new Texture())  {

}

Object::~Object()
{
	delete mesh;
	delete shader;
	delete texture;
}

bool Object::Initialize(ID3D11Device* device, const wchar_t* texturePath) {
	if (shader) {
		shader->CreateVertexShader(device,L"BasicShader.hlsl");
		shader->CreatePixelShader(device,L"BasicShader.hlsl");
	}
	else
		return false;

	if (mesh)
		mesh->Initialize(device);
	else
		return false;

	if (texture)
		return texture->Load(device, texturePath);
	else
		return false;
}

void Object::Render(ID3D11DeviceContext* context)  {
	if (!isVisible || !mesh || !shader)
		return;

	shader->Bind(context);
	texture->Bind(context);
	mesh->Render(context);
}