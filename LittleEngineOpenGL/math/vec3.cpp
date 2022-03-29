
#include "vec3.h"


namespace le
{


vec3 vec3::cross(vec3 a, vec3 b) {
	return {
		a.y * b.z - b.y * a.z,
		a.z * b.x - b.z * a.x,
		a.x * b.y - b.x * a.y
	};
}


f32 vec3::dot(vec3 a, vec3 b) {
	const vec3 tmp{ a * b };
	return tmp.x + tmp.y + tmp.z;
}


f32 vec3::length(vec3 v) {
	return std::sqrt(vec3::dot(v, v));
}


vec3 vec3::normalize(vec3 v) {
	const f32 magnitude{ length(v) };
	if (magnitude == 0.f) {
		static_assert(true, "vec3::normalize(magnitude=0.f) - cannot divide by zero!");
	}
	const f32 inverseMagnitude{ 1.f / magnitude };
	return v * inverseMagnitude;
}


b8 vec3::operator==(vec3 other) const {
	return ((x == other.x) && (y == other.y) && (z == other.z)) ? LTRUE : LFALSE;
}


b8 vec3::operator!=(vec3 other) const {
	return ~(*this == other);
}


}
