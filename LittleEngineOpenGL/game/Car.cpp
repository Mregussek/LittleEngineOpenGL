
#include "Car.h"


namespace le
{


void displayInfoAbout(const CarSpecification* pCarSpecs) {
	LLOG("CarSpecs Information Display...");
	auto displayVec = [](const vec3& v, const char* name) {
		std::cout << name << ": " << v.x << ", " << v.y << ", " << v.z << '\n';
	};
	std::cout << "Car Info: " << convertEnumToStr(pCarSpecs->type) << '\n';
	displayVec(pCarSpecs->position, "Position");
	displayVec(pCarSpecs->rotation, "Rotation");
	displayVec(pCarSpecs->scale, "Scale");
	std::cout << "Angle: " << pCarSpecs->angle << '\n';
}


}
