#include "plane.h"

Plane::Plane(double x, double y, double z, double X, double Y, double Z): Figure(x, y, z){
	X -= x;
	Y -= y;
	Z -= z;
	double d = sqrt(X*X + Y*Y + Z*Z);
	vec[0] = X/d;
	vec[1] = Y/d;
	vec[2] = Z/d;
}

Plane::Plane(double x, double y, double z, double X, double Y, double Z, float red, float green, float blue): Figure(x, y, z){
	double d = sqrt(X*X + Y*Y + Z*Z);
	vec[0] = X/d;
	vec[1] = Y/d;
	vec[2] = Z/d;
	setCol(red, green, blue);
}

Plane::Plane(double x, double y, double z, double X, double Y, double Z, float red, float green, float blue, bool ref, bool op, bool tra): Figure(x, y, z, ref, op, tra){
	double d = sqrt(X*X + Y*Y + Z*Z);
	vec[0] = X/d;
	vec[1] = Y/d;
	vec[2] = Z/d;
	setCol(red, green, blue);
}

double* Plane::getVec(){
	double* ptr = vec;
	return ptr;
}

void Plane::setVec(double x, double y, double z){
	vec[0] = x - *getPos();
	vec[1] = y - *(getPos() + 1);
	vec[2] = z - *(getPos() + 2);
}

double Plane::intersect(Ray& r){
	double dist = ((*getPos() - *r.getPos())*vec[0] + (*(getPos() + 1) - *(r.getPos() + 1))*vec[1] + (*(getPos() + 2) - *(r.getPos() + 2))*vec[2])/ (*(r.getVec() + 0)*vec[0] + *(r.getVec() + 1)*vec[1] + *(r.getVec() + 2)*vec[2]);
	if(dist < 0.001){
		return -1;
	}else{
		return dist;
	}
}

double* Plane::getN(Ray& r){
	double v[3];
	v[0] = -vec[0];
	v[1] = -vec[1];
	v[2] = -vec[2];
	if(vec[0]**r.getVec() + vec[1]**(r.getVec() + 1) + vec[2]**(r.getVec() + 2) < 0){
		double* ptr = v;
		return ptr;
	}else{
		double* ptr = vec;
		return ptr;
	}
}

double* Plane::getN(double* pos){
	double v[3];
	v[0] = -vec[0];
	v[1] = -vec[1];
	v[2] = -vec[2];
	double* ptr = v;
	return ptr;
}

Ray Plane::refract(Ray& r){
	return r;
}
