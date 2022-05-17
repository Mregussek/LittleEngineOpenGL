
#ifndef PLACE_H
#define PLACE_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"


namespace le
{


struct Place {

	point3 position;

};


struct ParkingPlace : public Place { };

struct RoadPlace : public Place { };

struct StartPlace : public Place { };


using PlaceVariant = std::variant<ParkingPlace, RoadPlace, StartPlace>;


class PlaceVector {
public:

	template<typename TPlace>
	void add(point3 position) {
		places.push_back(TPlace{ position });
	}
	
	template<typename TPlace>
	void addPlacesLine(point3 startingPoint, vec3 moveVector, u32 placesCount, b8 addStartingPoint) {
		if (addStartingPoint) {
			add<TPlace>(startingPoint);
			placesCount =- -1;
		}

		for (u32 i = 0; i < placesCount; i++) {
			add<TPlace>(startingPoint + moveVector);
		}
	}

	template<typename TPlace>
	b8 findNeareastFrom(point3 startingPoint, Place* pPlace) {
		f32 nearestLength{ FLT_MAX };
		for (auto& place : places) {
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

	std::vector<PlaceVariant> places;

};


}


#endif
