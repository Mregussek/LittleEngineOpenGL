
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


}
