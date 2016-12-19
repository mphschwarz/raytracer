#ifndef FIGURE_H
#define FIGURE_H

#include "ray.h"
#include "color.h"

#include <cmath>

class Figure{
	private:
		double pos[3];	//position
		double rho, sigma;	//albedo and roughness
		double A, B;	//ON-shading constants
		Color c;	//color
		bool reflective;
		bool opaque;
		bool translucent;

	public:
		Figure();
		Figure(double, double, double);
		Figure(double, double, double, bool, bool, bool);
		Figure(double, double, double, float, float, float);
		Figure(double, double, double, float, float, float, bool, bool, bool);

		void setPos(double x, double y, double z);
		double* getPos();
		void setCol(float, float, float);
		Color& getCol();
		bool& getReflective();
		bool& getOpaque();
		bool& getTranslucent();
		virtual double intersect(Ray&);	//distance from ray origin to figure
		virtual double* getN(Ray&);	//normal vector from point of intersection of figure and ray
  		virtual double* getN(double*);	//normal vector from point on figure
		//virtual Ray reflect(&Ray);
		virtual Ray refract(Ray&);
};

#endif
