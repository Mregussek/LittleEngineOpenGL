
#include "Mesh.h"
#include "filesystem/path.h"


namespace le
{


std::string convertEnumToStr(MeshType type) {
    switch (type) {
    case MeshType::CONNECTOR_01: return "CONNECTOR_01";
    case MeshType::CONNECTOR_02: return "CONNECTOR_02";
    case MeshType::ROAD: return "ROAD";
    case MeshType::START_PLACE: return "START_PLACE";
    case MeshType::PARKING_SPOT: return "PARKING_SPOT";
    default: return "NONE";
    }
}


static vec3 convert(objl::Vector3 v) {
    return vec3{ v.X, v.Y, v.Z };
}


b8 ObjMesh::loadFile(const std::string& path) {
    LLOG("Loading obj file: " + path);
    mPath = path;
    if (!Path::exists(path.c_str())) {
        LLOG("Selected obj file does not exist!");
        return mLoaded = LFALSE;
    }

    objl::Loader Loader;
    const b8 loadedModelProperly{ Loader.LoadFile(path) };
    
    if (!loadedModelProperly) {
        LLOG("Couldnt load properly obj file " + mPath + "!");
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

    LLOG("Loaded properly obj file: " + mPath);
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


f32* ObjMesh::vertices() { return mVertices.data(); }
u32 ObjMesh::countVertices() const { return (u32)mVertices.size(); }
u32 ObjMesh::sizeofVertices() const { return (u32)(mVertices.size() * sizeof(decltype(mVertices[0]))); }

u32* ObjMesh::indices() { return mIndices.data(); }
u32 ObjMesh::countIndices() const { return (u32)mIndices.size(); }
u32 ObjMesh::sizeofIndices() const { return (u32)(mIndices.size() * sizeof(decltype(mIndices[0]))); }


const std::string ObjMesh::getPath() const {
    return mPath;
}

MeshType ObjMesh::getType() const {
    return mType;
}

void ObjMesh::setType(MeshType type) {
    mType = type;
}


f32* CubeMesh::vertices() { return mVertices.data(); }
u32 CubeMesh::countVertices() const { return (u32)mVertices.size(); }
u32 CubeMesh::sizeofVertices() const { return (u32)(mVertices.size() * sizeof(decltype(mVertices[0]))); }

u32* CubeMesh::indices() { return mIndices.data(); }
u32 CubeMesh::countIndices() const { return (u32)mIndices.size(); }
u32 CubeMesh::sizeofIndices() const { return (u32)(mIndices.size() * sizeof(decltype(mIndices[0]))); }

MeshType CubeMesh::getType() const { return MeshType::NONE; }

void ObjMeshFactory::init() {
    LLOG("Initializing obj mesh factory...");
    for (u32 i = 0; i < mPaths.size(); i++) {
        const auto [path, type] = mPaths[i];
        LLOG("Emplacing at mesh factory object located at: " + path);
        auto& objMesh{ mVector.emplace_back() };
        objMesh.setType(type);
        objMesh.loadFile(path.c_str());
        LLOG("Loading end status " + objMesh.getPath() + " : " + (objMesh.loadedProperly() ? "TRUE" : "FALSE"));
    }
    LLOG("Initialized obj mesh factory!");
}

ObjMesh* ObjMeshFactory::get(MeshType type) {
    for (ObjMesh& objMesh : mVector) {
        if (objMesh.getType() == type) {
            LLOG("Returing correct obj mesh from factory: " + objMesh.getPath());
            return &objMesh;
        }
    }
    LLOG("Could not find correct obj mesh at factory! " + convertEnumToStr(type));
    return nullptr;
}

ObjMesh* ObjMeshFactory::get(u32 i) {
    return &mVector[i];
}

void ObjMeshFactory::close() {
    LLOG("Clearing Obj Mesh Factory...");
    mVector.clear();
}

u32 ObjMeshFactory::size() const {
    return (u32)mVector.size();
}


static void displayVec(vec4& v, const char* name) {
    std::cout << name << ": " << v.x << ", " << v.y << ", " << v.z << ", " << v.w << '\n';
}

static void displayVec(vec3& v, const char* name) {
    std::cout << name << ": " << v.x << ", " << v.y << ", " << v.z << '\n';
}

void displayInfoAbout(MeshRuntimeSpecification* pSpecs) {
    LLOG("MeshRuntimeSpecs Info...");
    std::cout << "MeshRuntimeSpecs Info: " << convertEnumToStr(pSpecs->type) << '\n';
    displayVec(pSpecs->position, "Position");
    displayVec(pSpecs->rotation, "Rotation");
    displayVec(pSpecs->scale, "Scale");
    displayVec(pSpecs->color, "Color");
}


}
