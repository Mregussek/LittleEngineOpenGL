
#ifndef VEC4_H
#define VEC4_H


#include "includes.h"
#include "defines.h"


namespace le
{


struct vec4 {

    union { f32 x, r; };
    union { f32 y, g; };
    union { f32 z, b; };
    union { f32 w, a; };

    template<typename T> vec4 add(T v) const;
    template<typename T> vec4 subtract(T f) const;
    template<typename T> vec4 multiply(T f) const;
    template<typename T> vec4 divide(T f) const;

    b8 operator==(vec4 other) const;
    b8 operator!=(vec4 other) const;

    static vec4 random();
    static vec4 random(f32 min, f32 max);

};


vec4 operator+(vec4 left, vec4 right);
vec4 operator-(vec4 left, vec4 right);
vec4 operator*(vec4 left, vec4 right);
vec4 operator/(vec4 left, vec4 right);

vec4 operator+(vec4 left, f32 right);
vec4 operator-(vec4 left, f32 right);
vec4 operator*(vec4 left, f32 right);
vec4 operator/(vec4 left, f32 right);

vec4 operator+(f32 left, vec4 right);
vec4 operator-(f32 left, vec4 right);
vec4 operator*(f32 left, vec4 right);
vec4 operator/(f32 left, vec4 right);


using color4 = vec4;
using point4 = vec4;
using vector4 = vec4;


}


#include "vec4.inl"


#endif
