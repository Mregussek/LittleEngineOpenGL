
#include "vec4.h"


namespace le
{


b8 vec4::operator==(vec4 other) const {
	return (
		(x == other.x) &&
		(y == other.y) &&
		(z == other.z) &&
		(w == other.w)
			) ? LTRUE : LFALSE;
}


b8 vec4::operator!=(vec4 other) const {
	return ~(*this == other);
}


vec4 vec4::random() {
	return {
		generateRandom(),
		generateRandom(),
		generateRandom(),
		generateRandom()
	};
}


vec4 vec4::random(f32 min, f32 max) {
	return {
		generateRandom(min, max),
		generateRandom(min, max),
		generateRandom(min, max),
		generateRandom(min, max)
	};
}


vec4 operator+(vec4 left, vec4 right) {
	return left.add(right);
}


vec4 operator-(vec4 left, vec4 right) {
	return left.subtract(right);
}


vec4 operator*(vec4 left, vec4 right) {
	return left.multiply(right);
}


vec4 operator/(vec4 left, vec4 right) {
	return left.divide(right);
}


vec4 operator+(vec4 left, f32 right) {
	return left.add(right);
}


vec4 operator-(vec4 left, f32 right) {
	return left.subtract(right);
}


vec4 operator*(vec4 left, f32 right) {
	return left.multiply(right);
}


vec4 operator/(vec4 left, f32 right) {
	return left.divide(right);
}


vec4 operator+(f32 left, vec4 right) {
	return right.add(left);
}


vec4 operator-(f32 left, vec4 right) {
	return right.subtract(left);
}


vec4 operator*(f32 left, vec4 right) {
	return right.multiply(left);
}


vec4 operator/(f32 left, vec4 right) {
	return right.divide(left);
}


}
