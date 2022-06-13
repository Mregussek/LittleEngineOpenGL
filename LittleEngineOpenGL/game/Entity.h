
#ifndef ENTITY_H
#define ENTITY_H


#include "Place.h"


namespace le
{


class Entity {
public:

    virtual void start() { }

    virtual void update() { }

    virtual void close() { }

};


using EntityPointerVector = std::vector<Entity*>;


class ParkingEntity : public Entity {
public:

    void start() override {
        const rotation3 r{ 1.f, 1.f, 1.f };
        const scale3 s{ 0.2f, 0.2f, 0.2f };
        mPlaceVector.add<StartPlace>(point3{ 0.f, 0.f, 0.f }, rotation3{ r }, scale3{ 1.f, 1.f, 1.f });
        mPlaceVector.add<RoadPlace>(point3{ 0.f, 0.f, -3.f }, rotation3{ r }, scale3{ s });
        mPlaceVector.add<Connector01Place>(point3{ 0.f, 0.f, -6.f }, rotation3{ r }, scale3{ s });
        mPlaceVector.add<Connector02Place>(point3{ 0.f, 0.f, -9.f }, rotation3{ r }, scale3{ s });
        mPlaceVector.add<ParkingPlace>(point3{ 0.f, 0.f, -12.f }, rotation3{ r }, scale3{ s });
    }

    void update() override {

    }

    void close() override {
        mPlaceVector.clearAll();
    }

    const PlaceVector& getPlaceVector() const { return mPlaceVector; }

private:

    PlaceVector mPlaceVector;

};


class CarEntity : public Entity {
public:

    void start() override {

    }

    void update() override {

    }

    void close() override {

    }

};


}


#endif
