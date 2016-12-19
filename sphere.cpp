#include "sphere.h"

Sphere::Sphere(double x, double y, double z, double r): Figure(x, y, z){
	setCol(1,1,1);
	rad = r;
}

Sphere::Sphere(double x, double y, double z, double r, float red, float green, float blue): Figure(x, y, z){
	setCol(red, green, blue);
	rad = r;
}

Sphere::Sphere(double x, double y, double z, double r, float red, float green, float blue, bool ref, bool op, bool tra): Figure(x, y, z, ref, op, tra){
	setCol(red, green, blue);
	rad = r;
}

double& Sphere::getRad(){
	return rad;
}

double Sphere::intersect(Ray& r){
	double det = pow(*r.getVec()*(*r.getPos() - *getPos()) +
		*(r.getVec() + 1)*(*(r.getPos() + 1) - *(getPos() + 1)) +
		*(r.getVec() + 2)*(*(r.getPos() + 2) - *(getPos() + 2)), 2) -
		(pow(*r.getVec(),2) + pow(*(r.getVec() + 1), 2) + pow(*(r.getVec() + 2), 2))*
		(pow(*r.getPos() - *getPos(), 2) + pow(*(r.getPos() + 1) - *(getPos() + 1), 2) +
		pow(*(r.getPos() + 2) - *(getPos() + 2), 2) - pow(rad, 2));

	if(det <= 0){
		return -1;	//sphere doesn't intersect r
	}else{
		double dist = -(*r.getVec()*(*r.getPos() - *getPos()) +
			*(r.getVec() + 1)*(*(r.getPos() + 1) - *(getPos() + 1)) +
			*(r.getVec() + 2)*(*(r.getPos() + 2) - *(getPos() + 2)) +
			sqrt(det))/(pow(*r.getVec(), 2) + pow(*(r.getVec() + 1), 2) + pow(*(r.getVec() + 2), 2));
		if(dist > 0.01){
			return dist;	//returns point closer to r.pos
		}else{
			dist = -(*r.getVec()*(*r.getPos() - *getPos()) +
				*(r.getVec() + 1)*(*(r.getPos() + 1) - *(getPos() + 1)) +
				*(r.getVec() + 2)*(*(r.getPos() + 2) - *(getPos() + 2)) -
				sqrt(det))/(pow(*r.getVec(), 2) + pow(*(r.getVec() + 1), 2) + pow(*(r.getVec() + 2), 2));
			if(dist > 0.01){
				return dist;	//returns point further from r.pos
			}else{
				return -1;	//sphere is behind r.pos
			}
		}
	}
}

double* Sphere::getN(Ray& r){
	assert(intersect(r) >= 0);
	double norm[3];
	double dist = intersect(r);	//distance to intersection
	norm[0] = *r.getVec() * dist + *r.getPos() - *getPos();
	norm[1] = *(r.getVec() + 1) * dist + *(r.getPos() + 1) - *(getPos() + 1);
	norm[2] = *(r.getVec() + 2) * dist + *(r.getPos() + 2) - *(getPos() + 2);
	double d= sqrt(norm[0] * norm[0] + norm[1] * norm[1] + norm[2] * norm[2]);
	norm[0] /= d;
	norm[1] /= d;
	norm[2] /= d;
	double* ptr = norm;
	return ptr;
}

double* Sphere::getN(double* pos){
	double norm[3];
	norm[0] = *pos - *getPos();
	norm[1] = *(pos + 1) - *(getPos() + 1);
	norm[2] = *(pos + 2) - *(getPos() + 2);
	double d = sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);
	norm[0] /= d;
	norm[1] /= d;
	norm[2] /= d;
	double* ptr = norm;
	return ptr;
}

Ray Sphere::refract(Ray& r){
	double n1 = 1.00;
	double n2 = 1.46;
	Ray temp(*r.getPos() + *r.getVec() * intersect(r),
		*(r.getPos() + 1) + *(r.getVec() + 1) * intersect(r),
		*(r.getPos() + 2) + *(r.getVec() + 2) * intersect(r),
		n1/n2*(getN(r))
		0,0,0);
	return temp;
}
