
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

    void start() override;
    void update() override;
    void close() override;

    const PlaceVector& getPlaceVector() const;

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
