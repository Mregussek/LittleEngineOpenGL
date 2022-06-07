
#ifndef RENDERER_H
#define RENDERER_H


#include "includes.h"
#include "defines.h"
#include "math/vec4.h"


namespace le
{


class Model;
class Shader;
class Camera;
class Buffer;
class PointLight;
struct MeshSpecification;


struct RendererSpecification {

	color4 clearColor{ 0.f, 0.f, 0.f, 1.f };
	Camera* pCamera{ nullptr };

};


struct RenderModelSpecification {
	
	Shader* pShader{ nullptr };
	MeshSpecification* pMeshSpecs{ nullptr };
	Buffer* pBuffer{ nullptr };
	PointLight* pPointLight{ nullptr };
	void(*pUniformSetupFunc)(Camera* pCamera, Shader* pShader, MeshSpecification* pMeshSpecs, PointLight* pPointLight);

};


class Renderer {
public:

	b8 init(RendererSpecification _renderSpecs);
	void updateSpecs(RendererSpecification _renderSpecs);

	void clearScreen() const;
	void draw(const RenderModelSpecification& renderModelSpecs) const;

private:

	RendererSpecification mRenderSpecs;

};


}


#endif
