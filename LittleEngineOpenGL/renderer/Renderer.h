
#ifndef RENDERER_H
#define RENDERER_H


#include "includes.h"
#include "defines.h"
#include "math/vec4.h"


namespace le
{


class Buffer;
class Shader;
class Camera;


struct RendererSpecification {

	color4 clearColor{ 0.f, 0.f, 0.f, 1.f };
	Camera* pCamera{ nullptr };

};


class Renderer {
public:

	b8 init(RendererSpecification _renderSpecs);

	void clearScreen() const;
	void draw(Shader* pShader, Buffer* pBuffer, void(*uniformSetupFunc)(Camera* pCamera, Shader* pShader)) const;

private:

	RendererSpecification renderSpecs;

};


}


#endif
