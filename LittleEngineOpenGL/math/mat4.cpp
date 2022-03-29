
#include "mat4.h"
#include "vec3.h"


namespace le
{


mat4::mat4(f32 diagonal) {
	for (u32 i = 0; i < 4 * 4; i++) {
		elements[i] = 0.0f;
	}
	for (u32 i = 0; i < 4; i++) {
		elements[i + i * 4] = diagonal;
	}
}


mat4 mat4::identity() {
	return mat4(1.0f);
}


mat4 mat4::perspective(f32 fov, f32 aspectRatio, f32 near, f32 far) {
	mat4 result(1.0f);
	const f32 tanfov2{ tan(fov / 2.f) };

	result.elements[0 + 0 * 4] = 1.f / (aspectRatio * tanfov2);
	result.elements[1 + 1 * 4] = 1.f / tanfov2;
	result.elements[2 + 2 * 4] = -((far + near) / (far - near));
	result.elements[3 + 2 * 4] = -1.f;
	result.elements[2 + 3 * 4] = -((2.f * far * near) / (far - near));

	return result;
}


mat4 mat4::lookAt(vec3 eye, vec3 center, vec3 y) {
	const vec3 fwd{ vec3::normalize(center - eye) };
	const vec3 side{ vec3::normalize(vec3::cross(fwd, y)) };
	const vec3 up{ vec3::cross(side, fwd) };

	mat4 rtn{ 1.f };

	rtn[0 + 0 * 4] = side.x;
	rtn[1 + 0 * 4] = up.x;
	rtn[2 + 0 * 4] = -fwd.x;
	rtn[3 + 0 * 4] = 0.f;
	rtn[0 + 1 * 4] = side.y;
	rtn[1 + 1 * 4] = up.y;
	rtn[2 + 1 * 4] = -fwd.y;
	rtn[3 + 1 * 4] = 0.f;
	rtn[0 + 2 * 4] = side.z;
	rtn[1 + 2 * 4] = up.z;
	rtn[2 + 2 * 4] = -fwd.z;
	rtn[3 + 2 * 4] = 0.f;
	rtn[0 + 3 * 4] = -vec3::dot(side, eye);
	rtn[1 + 3 * 4] = -vec3::dot(up, eye);
	rtn[2 + 3 * 4] = vec3::dot(fwd, eye);
	rtn[3 + 3 * 4] = 1.0f;

	return rtn;
}


mat4 mat4::translation(vec3 v) {
	mat4 result(1.0f);
	result.elements[0 + 3 * 4] = v.x;
	result.elements[1 + 3 * 4] = v.y;
	result.elements[2 + 3 * 4] = v.z;

	return result;
}


mat4 mat4::rotation(f32 angle, vec3 axis) {
	mat4 result(1.0f);

	const f32 cosine{ cos(angle) };
	const f32 sine{ sin(angle) };
	const f32 neg_cosine{ 1.0f - cosine };

	const vec3 ax{ vec3::normalize(axis) };
	const f32 x{ ax.x };
	const f32 y{ ax.y };
	const f32 z{ ax.z };

	result.elements[0 + 0 * 4] = cosine + x * x * neg_cosine;
	result.elements[1 + 0 * 4] = y * x * neg_cosine + z * sine;
	result.elements[2 + 0 * 4] = z * x * neg_cosine - y * sine;

	result.elements[0 + 1 * 4] = x * y * neg_cosine - z * sine;
	result.elements[1 + 1 * 4] = cosine + y * y * neg_cosine;
	result.elements[2 + 1 * 4] = z * y * neg_cosine + x * sine;

	result.elements[0 + 2 * 4] = x * z * neg_cosine + y * sine;
	result.elements[1 + 2 * 4] = y * z * neg_cosine - x * sine;
	result.elements[2 + 2 * 4] = cosine + z * z * neg_cosine;

	return result;
}

mat4 mat4::scale(vec3 scal) {
	mat4 result(1.0f);
	result.elements[0 + 0 * 4] = scal.x;
	result.elements[1 + 1 * 4] = scal.y;
	result.elements[2 + 2 * 4] = scal.z;

	return result;
}


b8 mat4::compare(const mat4& left, const mat4& right) {
	for (u32 i = 0; i < 16; i++) {
		if (left[i] != right[i]) {
			return LFALSE;
		}
	}

	return LTRUE;
};


const f32 mat4::operator[](u32 index) const {
	if (index >= 4 * 4) {
		static_assert(true, "matrix.elements[index] out of bound!\n");
	}
	return elements[index];
}


f32& mat4::operator[](u32 index) {
	if (index >= 4 * 4) {
		static_assert(true, "const matrix.elements[index] out of bound!\n");
	}
	return elements[index];
}


}
