#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>
#include <D3D11.h>

class Mesh;
class Shader;

class Object
{
public:
	Object(std::string name = "Object", Mesh* mesh = nullptr);
	virtual ~Object();

	bool Initialize(ID3D11Device* device);
	void Render(ID3D11DeviceContext* context);

	void SetName(const std::string& name) { this->name = name; }
	const std::string& GetName() const { return name; }

	bool IsActive() { return isActive; }
	void SetActive(bool isActive) { this->isActive = isActive; }

	bool IsVisible() { return isVisible; }
	void SetVisible(bool isVisible) { this->isVisible = isVisible; }

private:
	std::string name;

	bool isActive = true;
	bool isVisible = true;

	Mesh* mesh;
	Shader* shader;
};

#endif
