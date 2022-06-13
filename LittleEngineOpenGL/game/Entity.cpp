
#include "Entity.h"
#include "renderer/Colors.h"


namespace le
{


void ParkingEntity::start() {
    const rotation3 frontRot{ 1.f, 1.f, 1.f };
    const rotation3 rightRot{ 0.f, 1.f, 0.f };
    const scale3 defaultScale{ 0.2f, 0.2f, 0.2f };
    const f32 defaultAngle{ 0.f };
    const f32 rightAngle90{ -90.f };
    mPlaceVector.add<StartPlace>(point3{ 0.f, 0.f, 0.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::blue(ColorType::DEFAULT), defaultAngle);
    mPlaceVector.add<RoadPlace>(point3{ 0.f, 0.f, -2.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::red(ColorType::DEFAULT), defaultAngle);
    mPlaceVector.add<RoadPlace>(point3{ 0.f, 0.f, -4.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::blue(ColorType::DEFAULT), defaultAngle);
    mPlaceVector.add<RoadPlace>(point3{ 0.f, 0.f, -6.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::yellow(ColorType::DEFAULT), defaultAngle);
    mPlaceVector.add<ParkingPlace>(point3{ 0.f, 0.f, -8.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::pink(ColorType::DEFAULT), defaultAngle);
    mPlaceVector.add<Connector01Place>(point3{ -2.f, 0.f, -8.f }, rotation3{ rightRot }, scale3{ defaultScale }, Colors::green(ColorType::DEFAULT), rightAngle90);
    // mPlaceVector.add<Connector02Place>(point3{ 0.f, 0.f, -10.f }, rotation3{ r }, scale3{ s }, Colors::pink(ColorType::DEFAULT));
}

void ParkingEntity::update() {

}

void ParkingEntity::close() {
    mPlaceVector.clearAll();
}

const PlaceVector& ParkingEntity::getPlaceVector() const { 
    return mPlaceVector;
}


}
