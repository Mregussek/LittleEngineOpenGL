
#include "Mesh.h"
#include "filesystem/path.h"


namespace le
{


static vec3 convert(objl::Vector3 v) {
    return vec3{ v.X, v.Y, v.Z };
}


b8 ObjMesh::loadFile(const char* path) {
    LLOG("Loading obj file...");
    if (!Path::exists(path)) {
        LLOG("Selected obj file does not exist!");
        return mLoaded = LFALSE;
    }

    objl::Loader Loader;
    const b8 loadedModelProperly{ Loader.LoadFile(std::string{ path }) };
    
    if (!loadedModelProperly) {
        LLOG("Couldnt load properly obj file!");
        return mLoaded = LFALSE;
    }

    for (u32 i = 0; i < Loader.LoadedMeshes.size(); i++) {
        objl::Mesh curMesh{ Loader.LoadedMeshes[i] };
        for (u32 j = 0; j < curMesh.Vertices.size(); j++) {
            appendVertex(convert(curMesh.Vertices[j].Position), convert(curMesh.Vertices[j].Normal));
        }

        for (u32 j = 0; j < curMesh.Indices.size(); j += 3) {
            appendTriangleIndices(curMesh.Indices[j], curMesh.Indices[j + 1], curMesh.Indices[j + 2]);
        }
    }

    LLOG("Loaded properly obj file!");
    return mLoaded = LTRUE;
}


b8 ObjMesh::loadedProperly() const {
    return mLoaded;
}


void ObjMesh::appendVertex(vec3 position, vec3 normal) {
    mVertices.push_back(position.x);
    mVertices.push_back(position.y);
    mVertices.push_back(position.z);
    mVertices.push_back(normal.x);
    mVertices.push_back(normal.y);
    mVertices.push_back(normal.z);
}

void ObjMesh::appendTriangleIndices(u32 a, u32 b, u32 c) {
    mIndices.push_back(a);
    mIndices.push_back(b);
    mIndices.push_back(c);
}


}
