#ifndef LENS_H
#define LENS_H

#include "figure.h"

class Lens: public Figure{
	private:
		double r;
		
	public:
		Lens(double, double, double, double, float, float, float);
		Lens(double, double, double);
		double& getR();
		double intersect(Ray&) override;
		double* getN(Ray&) override;
		
}

#endif
