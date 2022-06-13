
#ifndef UTILITIES_H
#define UTILITIES_H


#include "includes.h"
#include "defines.h"
#include "renderer/Mesh.h"


namespace le
{


class ParkingEntity;


f32 rotationFunction(f32 angle);

void fillMeshRuntimeSpecsWithParkingEntity(ParkingEntity* pParkingEntity, MeshRuntimeSpecificationVector* pMeshRunSpecsVector);


}


#endif
