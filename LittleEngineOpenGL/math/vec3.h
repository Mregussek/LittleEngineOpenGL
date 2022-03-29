
#ifndef VEC3_H
#define VEC3_H


#include "../includes.h"
#include "../defines.h"


namespace le
{


struct vec3 {

    union { f32 x, r; };
    union { f32 y, g; };
    union { f32 z, b; };

    template<typename T> vec3 add(T v) const;
    template<typename T> vec3 subtract(T f) const;
    template<typename T> vec3 multiply(T f) const;
    template<typename T> vec3 divide(T f) const;

    static vec3 cross(vec3 a, vec3 b);
    static f32 dot(vec3 a, vec3 b);
    static f32 length(vec3 v);
    static vec3 normalize(vec3 v);

	b8 operator==(vec3 other) const;
	b8 operator!=(vec3 other) const;

};


template<typename T, typename U> vec3 operator+(T left, U right);
template<typename T, typename U> vec3 operator-(T left, U right);
template<typename T, typename U> vec3 operator*(T left, U right);
template<typename T, typename U> vec3 operator/(T left, U right);


using color3 = vec3;
using point3 = vec3;
using vector3 = vec3;


}


#include "vec3.inl"


#endif
