
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
	b8 visited{ LFALSE };

	virtual MeshType getType() const { return MeshType::NONE; }

};


using PlacePointerVector = std::vector<Place*>;


void displayInfoAbout(Place* pPlace);


struct Road01Place : public Place {
	
	MeshType getType() const override { return MeshType::ROAD_01; }

};


struct Road02Place : public Place {

	MeshType getType() const override { return MeshType::ROAD_02; }

};


struct Road03Place : public Place {

	MeshType getType() const override { return MeshType::ROAD_03; }

};


struct ParkingPlace : public Place {

	MeshType getType() const override { return MeshType::PARKING_SPOT; }

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

	void clearAll();
	
	Place* get(u32 i) const;
	Place* getFirstFoundType(MeshType type) const;
	u32 size() const;

	Place* findClosestPlace(point3 startingPoint, MeshType type, b8(*ifEquation)(Place*, MeshType)) const;

private:

	PlacePointerVector mPlaces;

};


}


#endif
