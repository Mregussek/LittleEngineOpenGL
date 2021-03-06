
#ifndef MAT4_INL
#define MAT4_INL


#include "mat4.h"


namespace le
{


template<typename T> T mat4::getColumn(u32 i) const {
	if constexpr (std::is_same<T, vec3>::value) {
		return {
			elements[0 + i * 4],
			elements[1 + i * 4],
			elements[2 + i * 4]
		};
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return {
			elements[0 + i * 4],
			elements[1 + i * 4],
			elements[2 + i * 4],
			elements[3 + i * 4]
		};
	}
	LLOG("ERROR");
}


template<typename T> T mat4::getRow(u32 i) const {
	if constexpr (std::is_same<T, vec3>::value) {
		return {
			elements[i + 0 * 4],
			elements[i + 1 * 4],
			elements[i + 2 * 4]
		};
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return {
			elements[i + 0 * 4],
			elements[i + 1 * 4],
			elements[i + 2 * 4],
			elements[i + 3 * 4]
		};
	}
	LLOG("ERROR");
}


template<typename T, typename U> U mat4::multiply(const T& other) const {
	if constexpr (std::is_same<T, vec4>::value && std::is_same<U, vec4>::value) {
		return mat4::multiplyMat4Vec4(*this, other);
	}
	else if constexpr (std::is_same<T, mat4>::value && std::is_same<U, mat4>::value) {
		return mat4::multiplyMat4Mat4(*this, other);
	}
	LLOG("ERROR, typenames T and U are not correct!");
	return U();
}


}


#endif
