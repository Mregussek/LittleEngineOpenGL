
#ifndef COLORS_H
#define COLORS_H


#include "math/vec4.h"



namespace le
{


enum class ColorType {
	DEFAULT, LIGHT, DARK
};


struct Colors {
	
	static constexpr color4 red(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 1.f, 0.5f, 0.5f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.8f, 0.f, 0.f, 1.f }; }
		else { return { 1.f, 0.f, 0.f, 1.f }; }
	}

	static constexpr color4 blue(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 0.5f, 0.5f, 1.f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.0f, 0.0f, 0.8f, 1.f }; }
		else { return { 0.f, 0.f, 1.f, 1.f }; }
	}

	static constexpr color4 green(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 0.5f, 1.f, 0.5f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.f, 0.8f, 0.f, 1.f }; }
		else { return { 0.f, 1.f, 0.f, 1.f }; }
	}

	static constexpr color4 yellow(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 1.f, 1.f, 0.5f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.8f, 0.8f, 0.f, 1.f }; }
		else { return { 1.f, 1.f, 0.f, 1.f }; }
	}

	static constexpr color4 orange(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 1.f, 0.7f, 0.5f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.8f, 0.3f, 0.f, 1.f }; }
		else { return { 1.f, 0.5f, 0.f, 1.f }; }
	}

	static constexpr color4 pink(ColorType CT) {
		if (CT == ColorType::LIGHT) { return { 1.f, 0.5f, 1.f, 1.f }; }
		else if (CT == ColorType::DARK) { return { 0.8f, 0.f, 0.8f, 1.f }; }
		else { return { 1.f, 0.f, 1.f, 1.f }; }
	}

	static constexpr color4 white{ 1.f, 1.f, 1.f, 1.f };
	static constexpr color4 black{ 0.f, 0.f, 0.f, 0.f };

};


}


#endif

