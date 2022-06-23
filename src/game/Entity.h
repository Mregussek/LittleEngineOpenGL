
#ifndef ENTITY_H
#define ENTITY_H


#include "Place.h"
#include "Car.h"


namespace le
{


class Entity {
public:

    virtual void start() { }

    virtual void update(f32 deltaTime) { }

    virtual void close() { }

};


using EntityPointerVector = std::vector<Entity*>;


class ParkingEntity : public Entity {
public:

    void start() override;
    void update(f32 deltaTime) override;
    void close() override;

    const PlaceVector& getPlaceVector() const;

private:

    PlaceVector mPlaceVector;

};


class CarEntity : public Entity {
public:

    void start() override;
    void update(f32 deltaTime) override;
    void close() override;

    void passParkingEntity(ParkingEntity* pEntity);
    const CarSpecification& getSpecs() const;

private:

    CarSpecification mCarSpecs{};
    ParkingEntity* pParkingEntity{ nullptr };
    vec3 mClosestDestination{};
    vec3 mParkingDestination{};
    vec3 mDirection{};
    f32 mStepSize{ 0.f };

};


}


#endif
