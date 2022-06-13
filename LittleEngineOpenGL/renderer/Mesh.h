
#ifndef MESH_H
#define MESH_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "math/vec4.h"


namespace le
{


struct MeshRuntimeSpecification {

    color4 color;

    point3 position;
    rotation3 rotation;
    scale3 scale;

    point3(*positionFunc)();
    std::pair<f32, rotation3>(*rotateFunc)();
    scale3(*scaleFunc)();

};


class Mesh {
public:

    virtual f32* vertices() { return nullptr; }
    virtual u32 countVertices() const { return 0; }
    virtual u32 sizeofVertices() const { return 0; }

    virtual u32* indices() { return nullptr; }
    virtual u32 countIndices() const { return 0; }
    virtual u32 sizeofIndices() const { return 0; }

};


class ObjMesh : public Mesh {
public:

    b8 loadFile(const char* path);

    b8 loadedProperly() const;

    f32* vertices() override;
    u32 countVertices() const override;
    u32 sizeofVertices() const override;

    u32* indices() override;
    u32 countIndices() const override;
    u32 sizeofIndices() const override;

private:

    void appendVertex(vec3 position, vec3 normal);
    void appendTriangleIndices(u32 a, u32 b, u32 c);

    std::vector<f32> mVertices{};
    std::vector<u32> mIndices{};
    u32 mID{ 0 };
    b8 mLoaded{ LFALSE };

};


using ObjMeshVector = std::vector<ObjMesh>;


class CubeMesh : public Mesh {
public:

    f32* vertices() override;
    u32 countVertices() const override;
    u32 sizeofVertices() const override;

    u32* indices() override;
    u32 countIndices() const override;
    u32 sizeofIndices() const override;

private:

    std::array<f32, 24> mVertices{
        -1.f, -1.f,  1.f, // 0
         1.f, -1.f,  1.f, // 1
        -1.f,  1.f,  1.f, // 2
         1.f,  1.f,  1.f, // 3
        -1.f, -1.f, -1.f, // 4
         1.f, -1.f, -1.f, // 5
        -1.f,  1.f, -1.f, // 6
         1.f,  1.f, -1.f  // 7
    };

    std::array<u32, 36> mIndices{
        // Top
        2, 6, 7,
        2, 3, 7,
        // Bottom
        0, 4, 5,
        0, 1, 5,
        // Left
        0, 2, 6,
        0, 4, 6,
        // Right
        1, 3, 7,
        1, 5, 7,
        // Front
        0, 2, 3,
        0, 1, 3,
        // Back
        4, 6, 7,
        4, 5, 7
    };

};


}


#endif
