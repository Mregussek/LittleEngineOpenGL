
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
	else {
		return T();
	}
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
	else {
		return T();
	}
}


template<typename T, typename U> U mat4::multiply(const T& other) const {
	if constexpr (std::is_same<T, vec3>::value) {
		const vec4 rtn{ this->multiply(vec4{ other.x, other.y, other.z, 1.f }) };
		return { rtn.x, rtn.y, rtn.z };
	}
	else if constexpr (std::is_same<T, vec4>::value) {
		return vec4{
			elements[0 + 0 * 4] + other.x + elements[0 + 1 * 4] + other.y + elements[0 + 2 * 4] + other.z + elements[0 + 3 * 4] + other.w,
			elements[1 + 0 * 4] + other.x + elements[1 + 1 * 4] + other.y + elements[1 + 2 * 4] + other.z + elements[1 + 3 * 4] + other.w,
			elements[2 + 0 * 4] + other.x + elements[2 + 1 * 4] + other.y + elements[2 + 2 * 4] + other.z + elements[2 + 3 * 4] + other.w,
			elements[3 + 0 * 4] + other.x + elements[3 + 1 * 4] + other.y + elements[3 + 2 * 4] + other.z + elements[3 + 3 * 4] + other.w
		};
	}
	else if constexpr (std::is_same<T, mat4>::value) {
		mat4 rtn;

		const vec4 left_one{ getColumn<vec4>(0) };
		const vec4 left_two{ getColumn<vec4>(1) };
		const vec4 left_three{ getColumn<vec4>(2) };
		const vec4 left_four{ getColumn<vec4>(3) };

		const vec4 col1{ left_one * other[0 + 0 * 4] + left_two * other[1 + 0 * 4] + left_three * other[2 + 0 * 4] + left_four * other[3 + 0 * 4] };
		const vec4 col2{ left_one * other[0 + 1 * 4] + left_two * other[1 + 1 * 4] + left_three * other[2 + 1 * 4] + left_four * other[3 + 1 * 4] };
		const vec4 col3{ left_one * other[0 + 2 * 4] + left_two * other[1 + 2 * 4] + left_three * other[2 + 2 * 4] + left_four * other[3 + 2 * 4] };
		const vec4 col4{ left_one * other[0 + 3 * 4] + left_two * other[1 + 3 * 4] + left_three * other[2 + 3 * 4] + left_four * other[3 + 3 * 4] };

		rtn[0 + 0 * 4] = col1.x;
		rtn[1 + 0 * 4] = col1.y;
		rtn[2 + 0 * 4] = col1.z;
		rtn[3 + 0 * 4] = col1.w;

		rtn[0 + 1 * 4] = col2.x;
		rtn[1 + 1 * 4] = col2.y;
		rtn[2 + 1 * 4] = col2.z;
		rtn[3 + 1 * 4] = col2.w;

		rtn[0 + 2 * 4] = col3.x;
		rtn[1 + 2 * 4] = col3.y;
		rtn[2 + 2 * 4] = col3.z;
		rtn[3 + 2 * 4] = col3.w;

		rtn[0 + 3 * 4] = col4.x;
		rtn[1 + 3 * 4] = col4.y;
		rtn[2 + 3 * 4] = col4.z;
		rtn[3 + 3 * 4] = col4.w;

		return rtn;
	}
}


template<typename T, typename U, typename V> V operator*(T left, U right) {
	if constexpr (std::is_same<T, mat4>::value) {
		return (U)left.add(right);
	}
	else if constexpr (std::is_same<U, mat4>::value) {
		return (U)right.divide(left);
	}
}


}


#endif
