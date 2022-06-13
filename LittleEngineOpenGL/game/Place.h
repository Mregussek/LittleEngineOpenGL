
#ifndef PLACE_H
#define PLACE_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "renderer/Mesh.h"


namespace le
{


struct Place {

	color4 color{};
	point3 position{};
	rotation3 rotation{};
	scale3 scale{};
	f32 angle{ 0.f };

	virtual MeshType getType() const { return MeshType::NONE; }

};


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


struct Connector01Place : public Place {
	
	MeshType getType() const override { return MeshType::CONNECTOR_01; }

};


struct Connector02Place : public Place { 

	MeshType getType() const override { return MeshType::CONNECTOR_02; }

};


struct ParkingPlace : public Place {

	MeshType getType() const override { return MeshType::PARKING_SPOT; }

};


struct RoadPlace : public Place { 

	MeshType getType() const override { return MeshType::ROAD; }

};


struct StartPlace : public Place {

	MeshType getType() const override { return MeshType::START_PLACE; }

};


class PlaceVector {
public:

	template<typename TPlace>
	void add(point3 position, rotation3 rotation, scale3 scale, color4 color, f32 angle) {
		TPlace* pPlace{ new TPlace };
		pPlace->position = position;
		pPlace->rotation = rotation;
		pPlace->scale = scale;
		pPlace->color = color;
		pPlace->angle = angle;
		mPlaces.push_back(pPlace);
	}

	void clearAll() {
		for (Place* pPlace : mPlaces) {
			delete pPlace;
		}
		mPlaces.clear();
	}
	
	Place* get(u32 i) const { return mPlaces[i]; }

	u32 size() const { return (u32)mPlaces.size(); }

	template<typename TPlace>
	b8 findNeareastFrom(point3 startingPoint, Place* pPlace) {
		f32 nearestLength{ FLT_MAX };
		for (auto& place : mPlaces) {
			std::visit(
				[](auto& arg) {
					using TArgPlace = std::decay<decltype(arg)>::type;
					if constexpr (!std::is_same<TArgPlace, TPlace>::value) {
						return;
					}
					
					const vec3 subtracted{ startingPoint - place.position };
					const f32 length{ vec3::length(subtracted) };
					if (length < nearestLength) {
						nearestLength = length;
						pPlace = &place;
					}
				},
			place);
		}

		if (nearestLength != FLT_MAX) {
			return LTRUE;
		}
		 
		return LFALSE;
	}

private:

	std::vector<Place*> mPlaces;

};


}


#endif
