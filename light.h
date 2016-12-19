#ifndef LIGHT_H
#define LIGHT_H

#include "figure.h"
#include "sphere.h"
#include "ray.h"
#include "color.h"

#include <cmath>
#include <vector>
#include <memory>

class Light: public Figure{
	public:
		Light(double, double, double, double);
		Light(double, double, double, double, float, float, float);
		double getL();
		void setL(double);
		double intersect(Ray&) override;
		Color shadeL(Ray&, std::vector< std::shared_ptr< Figure > >&, int&);
		Color shadeO(Ray&, std::vector< std::shared_ptr< Figure > >&, int&);
	private:
		double l;
};
#endif
