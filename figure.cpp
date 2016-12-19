#include "figure.h"

Figure::Figure(){}

Figure::Figure(double x, double y, double z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	c.r = 1;
	c.g = 1;
	c.b = 1;
	reflective = false;
}

Figure::Figure(double x, double y, double z, bool ref, bool op, bool tr){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	reflective = ref;
	opaque = op;
	translucent = tr;
}

Figure::Figure(double x, double y, double z, float red, float green, float blue){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	c.r = red;
	c.g = green;
	c.b = blue;
	reflective = false;
}

Figure::Figure(double x, double y, double z, float red, float green, float blue, bool ref, bool op, bool tr){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	c.r = red;
	c.g = green;
	c.b = blue;
	reflective = ref;
	opaque = op;
	translucent = tr;
}

void Figure::setPos(double x, double y, double z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Figure::setCol(float red, float green, float blue){
	c.r = red;
	c.g = green;
	c.b = blue;
}

double* Figure::getPos(){
	double *ptr = pos;
	return ptr;
}

bool& Figure::getReflective(){
	return reflective;
}

bool& Figure::getOpaque(){
	return opaque;
}

bool& Figure::getTranslucent(){
	return translucent;
}

double Figure::intersect(Ray&){
	return 0.00;
}

double* Figure::getN(Ray& r){
	return NULL;
}

double* Figure::getN(double* p){
	return NULL;
}

Ray Figure::refract(Ray& r){
	Ray R(0,0,0,1,1,1);
	return R;
}

Color& Figure::getCol(){
	return c;
}
