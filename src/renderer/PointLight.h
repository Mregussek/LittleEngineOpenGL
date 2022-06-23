
#ifndef POINTLIGHT_H
#define POINTLIGHT_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"


namespace le
{



struct PointLightSpecification {
	vec3 position{ 0.f, 0.f, 0.f };
	color3 color{ 1.f, 1.f, 1.f };
};


class PointLight {
public:

	PointLight(PointLightSpecification _specs) : mSpecs(_specs) { }

	vec3 getPosition() const { return mSpecs.position; }
	color3 getColor() const { return mSpecs.color; }

private:

	PointLightSpecification mSpecs{};

};


}


#endif
