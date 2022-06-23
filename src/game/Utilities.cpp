
#include "Utilities.h"
#include "Place.h"
#include "Entity.h"
#include "renderer/Mesh.h"


namespace le
{


f32 rotationFunction(f32 angle) {
    return LDEG2RAD(angle);
}


void fillMeshRuntimeSpecsWithParkingEntity(ParkingEntity* pParkingEntity, MeshRuntimeSpecificationVector* pMeshRunSpecsVector) {
    const PlaceVector& placeVector{ pParkingEntity->getPlaceVector() };
    for (u32 i = 0; i < placeVector.size(); i++) {
        LLOG("Emplacing MeshRuntimeSpecs at vector...");
        MeshRuntimeSpecification& meshRunSpecs{ pMeshRunSpecsVector->emplace_back() };
        Place* pPlace{ placeVector.get(i) };
        displayInfoAbout(pPlace);
        meshRunSpecs.position = pPlace->position;
        meshRunSpecs.rotation = pPlace->rotation;
        meshRunSpecs.scale = pPlace->scale;
        meshRunSpecs.color = pPlace->color;
        meshRunSpecs.rotateFunc = rotationFunction;
        meshRunSpecs.angle = pPlace->angle;
        meshRunSpecs.type = pPlace->getType();
        displayInfoAbout(&meshRunSpecs);
    }
    LLOG("Filled MeshRunTimeSpecs!");
}


void fillMeshRuntimeSpecsWithCarEntity(CarEntity* pCarEntity, MeshRuntimeSpecification* pMeshRunSpecs) {
    LLOG("Filling MeshRuntimeSpecs with car entity...");
    const auto& carSpecs{ pCarEntity->getSpecs() };
    pMeshRunSpecs->position = carSpecs.position;
    pMeshRunSpecs->rotation = carSpecs.rotation;
    pMeshRunSpecs->scale = carSpecs.scale;
    pMeshRunSpecs->color = carSpecs.color;
    pMeshRunSpecs->rotateFunc = rotationFunction;
    pMeshRunSpecs->angle = carSpecs.angle;
    pMeshRunSpecs->type = carSpecs.type;
    displayInfoAbout(&carSpecs);
    LLOG("Filled MeshRunTimeSpecs with car entity!");
}


}
