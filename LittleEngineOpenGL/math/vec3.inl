
#ifndef VEC3_INL
#define VEC3_INL


#include "vec3.h"


namespace le
{


template<typename T> vec3 vec3::add(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x + (T)v, y + (T)v, z + (T)v };
	}
	else if constexpr (std::is_same<T, vec3>::value) {
		return { x + v.x, y + v.y, z + v.z };
	}
	LLOG("ERROR");
}


template<typename T> vec3 vec3::subtract(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x - (T)v, y - (T)v, z - (T)v };
	}
	else if constexpr (std::is_same<T, vec3>::value) {
		return { x - v.x, y - v.y, z - v.z };
	}
	LLOG("ERROR");
}


template<typename T> vec3 vec3::multiply(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x * (T)v, y * (T)v, z * (T)v };
	}
	else if constexpr (std::is_same<T, vec3>::value) {
		return { x * v.x, y * v.y, z * v.z };
	}
	LLOG("ERROR");
}


template<typename T> vec3 vec3::divide(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x / (T)v, y / (T)v, z / (T)v };
	}
	else if constexpr (std::is_same<T, vec3>::value) {
		return { x / v.x, y / v.y, z / v.z };
	}
	LLOG("ERROR");
}


}


#endif VEC3_INL
