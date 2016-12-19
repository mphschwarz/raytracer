#ifndef CUBOID_H
#define CUBOID_H

#include "figure.h"

class Cuboid: public Figure{
	private:
		double* vec1[3];
		double* vec2[3];
	public:
		Figure(double, double, double, double, double, double, double, double, double);
		Figure(double, double, double, double, double, double, double, double, double, float, float, float);
		
		double* getVec1();
		double* getVec1();
		
		virtual intersect(Ray&) override;
		virtual getN(Ray&) override;
};

#endif
