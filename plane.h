#ifndef PLANE_H
#define Plane_H

#include "figure.h"

class Plane: public Figure{
	private:
		double vec[3];
	public:
		Plane(double, double, double, double, double, double);
		Plane(double, double, double, double, double, double, float, float, float);
		Plane(double, double, double, double, double, double, float, float, float, bool, bool, bool);
		double* getVec();
		void setVec(double, double, double);
		double intersect(Ray&) override;
		double* getN(Ray&) override;
  		double* getN(double*) override;
  		Ray refract(Ray&) override;
};

#endif
