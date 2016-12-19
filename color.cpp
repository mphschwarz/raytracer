#include "color.h"

Color::Color () : r (1), g (1), b (1){}

Color::Color (float R, float G, float B) : r (R), g (G), b (B){}

Color& Color::operator += (Color c){
	r += c.r;
	g += c.g;
	b += c.b;
	return *this;
}

Color& Color::operator -= (Color c){
	r -= c.r;
	g -= c.g;
	b -= c.b;
	return *this;
}

Color& Color::operator *= (float s){
	r *= s;
	g *= s;
	b *= s;
	return *this;
}

Color& Color::operator *= (Color s){
	r *= s.r;
	g *= s.g;
	b *= s.b;
	return *this;
}

Color Color::operator + (const Color& b){
	return *this += b;
}

Color Color::operator - (const Color& b){
	return *this -= b;
}

Color Color::operator * (const Color& b){
	return *this *= b;
}


Color Color::operator * (const float b){
	return *this *= b;
}

std::ostream& operator << (std::ostream& out, Color color){
    out << color.r << "," << color.g <<"," << color.b;
    return out;
}

bool operator == (const Color& a, const Color& b){
    return a.r == b.r && a.g == b.g && a.b == b.b;
}

bool operator != (const Color& a, const Color& b){
    return a.r != b.r || a.g != b.g || a.b != b.b;
}

Color AdjustColor(Color c)
{
    if (c.r>1) c.r=1;
    if (c.g>1) c.g=1;
    if (c.b>1) c.b=1;
    if (c.r<0) c.r=0;
    if (c.g<0) c.g=0;
    if (c.b<0) c.b=0;
    return c;
}


