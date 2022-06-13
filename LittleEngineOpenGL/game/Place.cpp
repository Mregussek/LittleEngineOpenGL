
#include "Place.h"


namespace le
{


void displayInfoAbout(Place* pPlace) {
	LLOG("Place Information Display...");
	auto displayVec = [](vec3& v, const char* name) {
		std::cout << name << ": " << v.x << ", " << v.y << ", " << v.z << '\n';
	};
	std::cout << "Place Info: " << convertEnumToStr(pPlace->getType()) << '\n';
	displayVec(pPlace->position, "Position");
	displayVec(pPlace->rotation, "Rotation");
	displayVec(pPlace->scale, "Scale");
	std::cout << "Angle: " << pPlace->angle << '\n';
}


void PlaceVector::clearAll() {
	for (Place* pPlace : mPlaces) {
		delete pPlace;
	}
	mPlaces.clear();
}


}
