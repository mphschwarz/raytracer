#ifndef SPHERE_H
#define SPHERE_H

#include "figure.h"

#include <cmath>

class Sphere: public Figure{
	private:
		double rad;
	public:
		Sphere(double, double, double, double);
		Sphere(double, double, double, double, float, float, float);
		Sphere(double, double, double, double, float, float, float, bool, bool, bool);
		double& getRad();
		double intersect(Ray&) override;
		double* getN(Ray&) override;
		double* getN(double*) override;
  		Ray refract(Ray&) override;

};

#endif
