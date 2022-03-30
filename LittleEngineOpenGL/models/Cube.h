
#ifndef CUBE_H
#define CUBE_H


#include "includes.h"
#include "defines.h"


namespace le
{


struct Cube {

    std::array<f32, 24> vertices{
        -1.f, -1.f,  0.5f, // 0
         1.f, -1.f,  0.5f, // 1
        -1.f,  1.f,  0.5f, // 2
         1.f,  1.f,  0.5f, // 3
        -1.f, -1.f, -0.5f, // 4
         1.f, -1.f, -0.5f, // 5
        -1.f,  1.f, -0.5f, // 6
         1.f,  1.f, -0.5f  // 7
    };

    std::array<u32, 36> indices{
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
