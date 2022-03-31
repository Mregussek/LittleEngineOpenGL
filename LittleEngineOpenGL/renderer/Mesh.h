
#ifndef MESH_H
#define MESH_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "math/vec4.h"


namespace le
{


struct MeshSpecification {

    color4 color;
    point3 position;
    rotation3 rotation;
    f32(*rotateFunc)();

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


class Cube : public Mesh {
public:

    f32* vertices() override { return mVertices.data(); }
    u32 countVertices() const override { return (u32)mVertices.size(); }
    u32 sizeofVertices() const override { return (u32)(mVertices.size() * sizeof(decltype(mVertices[0]))); }

    u32* indices() override { return mIndices.data(); }
    u32 countIndices() const override { return (u32)mIndices.size(); }
    u32 sizeofIndices() const override { return (u32)(mIndices.size() * sizeof(decltype(mIndices[0]))); }

private:

    std::array<f32, 24> mVertices{
        -1.f, -1.f,  0.5f, // 0
         1.f, -1.f,  0.5f, // 1
        -1.f,  1.f,  0.5f, // 2
         1.f,  1.f,  0.5f, // 3
        -1.f, -1.f, -0.5f, // 4
         1.f, -1.f, -0.5f, // 5
        -1.f,  1.f, -0.5f, // 6
         1.f,  1.f, -0.5f  // 7
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
