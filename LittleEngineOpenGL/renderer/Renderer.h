
#ifndef RENDERER_H
#define RENDERER_H


#include "../includes.h"
#include "../defines.h"


namespace le
{


class Buffer;
class Shader;


struct RenderClearColor {
	float r, g, b;
};


struct RendererSpecification {

	RenderClearColor clearColor{ 0.f, 0.f, 0.f };

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
