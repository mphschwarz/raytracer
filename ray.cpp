#include <cmath>

#include "ray.h"

Ray::Ray(double x, double y, double z, double X, double Y, double Z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
	X -= x;
	Y -= y;
	Z -= z;
	vec[0] = X/sqrt(X*X + Y*Y + Z*Z);
	vec[1] = Y/sqrt(X*X + Y*Y + Z*Z);
	vec[2] = Z/sqrt(X*X + Y*Y + Z*Z);
}

Ray::Ray(){
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	vec[0] = 0;
	vec[1] = 0;
	vec[2] = 0;
}

double* Ray::getPos(){
	double* ptr = pos;
	return ptr;
}

double* Ray::getVec(){
	double* ptr = vec;
	return ptr;
}

double& Ray::getL(){
	return length;
}

void Ray::setPos(double x, double y, double z){
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;
}

void Ray::setVec(double x, double y, double z){
	x -= pos[0];
	y -= pos[1];
	z -= pos[2];
	vec[0] = x/sqrt(x*x + y*y + z*z);
	vec[1] = y/sqrt(x*x + y*y + z*z);
	vec[2] = z/sqrt(x*x + y*y + z*z);
}

void Ray::setL(double l){
	length = l;
}

double* Ray::crossp(Ray& r){
	double out[3];
	out[0] = vec[1] * *(r.getVec() + 2) - vec[2] * *(r.getVec() + 1);
	out[1] = vec[2] * *(r.getVec() + 0) - vec[0] * *(r.getVec() + 2);
	out[2] = vec[0] * *(r.getVec() + 1) - vec[1] * *(r.getVec() + 0);
	double* ptr = out;
	return ptr;
}

double Ray::dotp(Ray& r) {
	double  out = vec[0] * *r.getVec() + vec[1] * *(r.getVec() + 1) + vec[2] * *(r.getVec() + 2);
	return out;
}
