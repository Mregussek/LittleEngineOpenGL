
#include "Entity.h"
#include "renderer/Colors.h"


namespace le
{


void ParkingEntity::start() {
    const rotation3 frontRot{ 1.f, 1.f, 1.f };
    const rotation3 yAxisRot{ 0.f, 1.f, 0.f };
    const scale3 defaultScale{ 0.2f, 0.2f, 0.2f };

    mPlaceVector.add<StartPlace>(point3{ 0.f, 0.f, 0.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::yellow(ColorType::DEFAULT), 0.f);
    mPlaceVector.add<Road01Place>(point3{ 0.f, 0.f, -2.f }, rotation3{ frontRot }, scale3{ defaultScale }, Colors::red(ColorType::DEFAULT), 0.f);

    mPlaceVector.add<Road03Place>(point3{ 0.f, 0.f, -4.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::blue(ColorType::DEFAULT), -90.f);

    mPlaceVector.add<Road02Place>(point3{ 2.f, 0.f, -4.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::yellow(ColorType::DEFAULT), 90.f);
    mPlaceVector.add<Road02Place>(point3{ 4.f, 0.f, -4.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::yellow(ColorType::DEFAULT), 90.f);

    mPlaceVector.add<Road03Place>(point3{ 6.f, 0.f, -4.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::blue(ColorType::DEFAULT), 90.f);

    mPlaceVector.add<ParkingPlace>(point3{ 2.f, 0.f, -6.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::pink(ColorType::DEFAULT), 180.f);
    mPlaceVector.add<ParkingPlace>(point3{ 4.f, 0.f, -6.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::pink(ColorType::DEFAULT), 180.f);
    mPlaceVector.add<ParkingPlace>(point3{ 6.f, 0.f, -6.f }, rotation3{ yAxisRot }, scale3{ defaultScale }, Colors::pink(ColorType::DEFAULT), 180.f);
}

void ParkingEntity::update(f32 deltaTime) {

}

void ParkingEntity::close() {
    mPlaceVector.clearAll();
}

const PlaceVector& ParkingEntity::getPlaceVector() const { 
    return mPlaceVector;
}


static b8 validateType(Place* pPlace, MeshType type) {
    if (pPlace->getType() == type) { return LTRUE; }
    else { return LFALSE; }
}

static b8 validateNotType(Place* pPlace, MeshType type) {
    if (pPlace->getType() != type) { return LTRUE; }
    else { return LFALSE; }
}


void CarEntity::start() {
    if (!pParkingEntity) {
        return;
    }

    mStepSize = 0.3f;

    // Adjusting start place to parking's start place
    Place* pStartPlace{ pParkingEntity->getPlaceVector().getFirstFoundType(MeshType::START_PLACE) };
    mCarSpecs.position = pStartPlace->position;

    // Other specs...
    mCarSpecs.rotation = { 1.f, 1.f, 1.f };
    mCarSpecs.scale = { 0.5f, 0.5f, 0.5f };
    mCarSpecs.color = Colors::orange(ColorType::DEFAULT);
    mCarSpecs.angle = 0.f;
    mCarSpecs.type = MeshType::CAR_01;

    // Calculating parking destination...
    const PlaceVector& placeVector{ pParkingEntity->getPlaceVector() };
    Place* pParkingSpot{ placeVector.findClosestPlace(mCarSpecs.position, MeshType::PARKING_SPOT, validateType) };
    mParkingDestination = pParkingSpot->position;

    // Calculating closest destination
    Place* pNextPlace{ placeVector.findClosestPlace(mCarSpecs.position, MeshType::START_PLACE, validateNotType) };
    pNextPlace->visited = LTRUE;
    mClosestDestination = pNextPlace->position;
    mDirection = mClosestDestination - mCarSpecs.position;
}

void CarEntity::update(f32 deltaTime) {
    if (!pParkingEntity) {
        return;
    }

    if (vec3::compare(mCarSpecs.position, mParkingDestination, mStepSize * 0.2f)) {
        return;
    }

    if (vec3::compare(mCarSpecs.position, mClosestDestination, mStepSize * 0.2f)) {
        Place* pNextPlace{ pParkingEntity->getPlaceVector().findClosestPlace(mCarSpecs.position, MeshType::START_PLACE, validateNotType) };
        pNextPlace->visited = LTRUE;
        mClosestDestination = pNextPlace->position;
        mDirection = mClosestDestination - mCarSpecs.position;
    }

    mCarSpecs.position = mCarSpecs.position + (deltaTime * mStepSize * mDirection);
}

void CarEntity::close() {

}

void CarEntity::passParkingEntity(ParkingEntity* pEntity) {
    pParkingEntity = pEntity;
}

const CarSpecification& CarEntity::getSpecs() const {
    return mCarSpecs;
}


}
