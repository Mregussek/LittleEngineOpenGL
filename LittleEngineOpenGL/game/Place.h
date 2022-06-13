
#ifndef PLACE_H
#define PLACE_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"


namespace le
{


struct Place {

	point3 position;
	rotation3 rotation;
	scale3 scale;

	virtual const char* getPath() const { return ""; }

};


struct Connector01Place : public Place {
	
	const char* getPath() const override { return "resources/connector_01.obj"; }

};


struct Connector02Place : public Place { 

	const char* getPath() const override { return "resources/connector_02.obj"; }

};


struct ParkingPlace : public Place {

	const char* getPath() const override { return "resources/parking_spot.obj"; }

};


struct RoadPlace : public Place { 

	const char* getPath() const override { return "resources/road.obj"; }

};


struct StartPlace : public Place {

	const char* getPath() const override { return "resources/cube.obj"; }

};


class PlaceVector {
public:

	template<typename TPlace>
	void add(point3 position, rotation3 rotation, scale3 scale) {
		mPlaces.push_back(new TPlace{ position, rotation, scale });
	}

	void clearAll() {
		for (Place* pPlace : mPlaces) {
			delete pPlace;
		}
		mPlaces.clear();
	}
	
	const Place* get(u32 i) const { return mPlaces[i]; }

	u32 size() const { return mPlaces.size(); }

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
