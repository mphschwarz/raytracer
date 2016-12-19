#ifndef COLOR_H
#define COLOR_H

#include <vector>
#include <fstream>
#include <algorithm>
#include <cassert>

struct Color{
	float r, g, b;

	Color ();
	Color (float, float, float);

	Color& operator += (Color);
	Color& operator -= (Color);
	Color& operator *= (float);
	Color& operator *= (Color);
	Color operator+(const Color&);
	Color operator-(const Color&);
	Color operator*(const Color&);
	Color operator*(const float);
};

	const Color Red (1, 0, 0);
	const Color Green (0, 1, 0);
	const Color Blue (0, 0, 1);
	const Color Black (0, 0, 0);
	const Color White (1, 1, 1);
#endif
