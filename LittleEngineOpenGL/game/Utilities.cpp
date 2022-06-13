
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
        le::MeshRuntimeSpecification& meshRunSpecs{ pMeshRunSpecsVector->emplace_back() };
        le::Place* pPlace{ placeVector.get(i) };
        le::displayInfoAbout(pPlace);
        meshRunSpecs.position = pPlace->position;
        meshRunSpecs.rotation = pPlace->rotation;
        meshRunSpecs.scale = pPlace->scale;
        meshRunSpecs.color = pPlace->color;
        meshRunSpecs.rotateFunc = rotationFunction;
        meshRunSpecs.angle = pPlace->angle;
        meshRunSpecs.type = pPlace->getType();
        le::displayInfoAbout(&meshRunSpecs);
    }
    LLOG("Filled MeshRunTimeSpecs!");
}


}
