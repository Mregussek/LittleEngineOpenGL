
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


class Parking : public Entity {
public:

    void start() override {
        placeVector.add<StartPlace>({ 0.f, 0.f, 0.f });
        placeVector.addPlacesLine<RoadPlace>({ 0.f, 0.f, 2.f }, { 0.f, 0.f, 2.f }, 6, LTRUE);
        placeVector.addPlacesLine<ParkingPlace>({ -2.f, 0.f, 2.f }, { 0.f, 0.f, 2.f }, 6, LTRUE);
        placeVector.addPlacesLine<ParkingPlace>({ 2.f, 0.f, 2.f }, { 0.f, 0.f, 2.f }, 6, LTRUE);
    }

    void update() override {

    }

    void close() override {

    }

private:

    PlaceVector placeVector;

};


class Car : public Entity {
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
