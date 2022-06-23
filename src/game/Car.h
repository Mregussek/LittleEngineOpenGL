
#ifndef CAR_H
#define CAR_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "renderer/Mesh.h"


namespace le
{


struct CarSpecification {

	color4 color{};

	point3 position{};
	rotation3 rotation{};
	scale3 scale{};

	f32 angle{ 0.f };

	MeshType type{ MeshType::NONE };

};


void displayInfoAbout(const CarSpecification* pCarSpecs);


}


#endif
