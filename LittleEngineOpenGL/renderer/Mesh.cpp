
#include "Mesh.h"


namespace le
{


b8 ObjMesh::loadFile(const char* path) {
    LLOG("Loading obj file...");
    objl::Loader Loader;
    const b8 loadedModelProperly{ Loader.LoadFile(std::string{ path }) };
    
    if (!loadedModelProperly) {
        LLOG("Couldnt load properly obj file!");
        return LFALSE;
    }

    for (u32 i = 0; i < Loader.LoadedMeshes.size(); i++) {
        objl::Mesh curMesh{ Loader.LoadedMeshes[i] };
        for (u32 j = 0; j < curMesh.Vertices.size(); j++) {
            appendVertex(curMesh.Vertices[j].Position.X, curMesh.Vertices[j].Position.Y, curMesh.Vertices[j].Position.Z);
        }

        for (u32 j = 0; j < curMesh.Indices.size(); j += 3) {
            appendTriangleIndices(curMesh.Indices[j], curMesh.Indices[j + 1], curMesh.Indices[j + 2]);
        }
    }

    LLOG("Loaded properly obj file!");
    return LTRUE;
}


void ObjMesh::appendVertex(f32 x, f32 y, f32 z) {
    mVertices.push_back(x);
    mVertices.push_back(y);
    mVertices.push_back(z);
}

void ObjMesh::appendTriangleIndices(u32 a, u32 b, u32 c) {
    mIndices.push_back(a);
    mIndices.push_back(b);
    mIndices.push_back(c);
}


}
