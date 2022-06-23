
#ifndef VEC4_INL
#define VEC4_INL


#include "vec4.h"


namespace le
{


template<typename T> vec4 vec4::add(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x + (T)v, y + (T)v, z + (T)v, w + (T)v };
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return { x + v.x, y + v.y, z + v.z, w + v.w };
	}
	LLOG("ERROR");
}


template<typename T> vec4 vec4::subtract(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x - (T)v, y - (T)v, z - (T)v, w - (T)v };
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return { x - v.x, y - v.y, z - v.z, w - v.w };
	}
	LLOG("ERROR");
}


template<typename T> vec4 vec4::multiply(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x * (T)v, y * (T)v, z * (T)v, w * (T)v };
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return { x * v.x, y * v.y, z * v.z, w * v.w };
	}
	LLOG("ERROR");
}


template<typename T> vec4 vec4::divide(T v) const {
	if constexpr (std::is_arithmetic<T>::value && std::is_convertible<T, f32>::value) {
		return { x / (T)v, y / (T)v, z / (T)v, w / (T)v };
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return { x / v.x, y / v.y, z / v.z, w / v.w };
	}
	LLOG("ERROR");
}


}


#endif VEC4_INL
