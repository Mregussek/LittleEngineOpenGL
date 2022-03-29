
#ifndef RENDERER_H
#define RENDERER_H


#include "../includes.h"
#include "../defines.h"
#include "../math/vec3.h"


namespace le
{


class Buffer;
class Shader;


struct RendererSpecification {

	color3 clearColor{ 0.f, 0.f, 0.f };

};


class Renderer {
public:

	b8 init(RendererSpecification _renderSpecs);

	void clearScreen() const;
	void draw(Shader* pShader, Buffer* pBuffer) const;

private:

	RendererSpecification renderSpecs;

};


}


#endif
