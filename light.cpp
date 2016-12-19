#include "light.h"
#include <iostream>

Light::Light(double x, double y, double z, double li): Figure(x, y, z){
	l = li*30000000;
	setCol(1, 1, 1);
}

Light::Light(double x, double y, double z, double li, float red, float green, float blue): Figure(x, y, z){
	setCol(red, green, blue);
	l = li;
}

double Light::getL(){
	return l;
}

void Light::setL(double li){
	l = li;
}

double Light::intersect(Ray& r){
	double det = pow(*r.getVec()*(*r.getPos() - *getPos()) +
		*(r.getVec() + 1)*(*(r.getPos() + 1) - *(getPos() + 1)) +
		*(r.getVec() + 2)*(*(r.getPos() + 2) - *(getPos() + 2)), 2) -
		(pow(*r.getVec(),2) + pow(*(r.getVec() + 1), 2) + pow(*(r.getVec() + 2), 2))*
		(pow(*r.getPos() - *getPos(), 2) +
		pow(*(r.getPos() + 1) - *(getPos() + 1), 2) +
		pow(*(r.getPos() + 2) - *(getPos() + 2), 2) -
		pow(1, 2));

	if(det <= 0){
		return -2;
	}else{
		double dist = -(*r.getVec()*(*r.getPos() - *getPos()) + *(r.getVec() + 1)*
		(*(r.getPos() + 1) - *(getPos() + 1)) + *(r.getVec() + 2)*(*(r.getPos() + 2) - *(getPos() + 2)) + sqrt(det))/
		(pow(*r.getVec(), 2) + pow(*(r.getVec() + 1), 2) + pow(*(r.getVec() + 2), 2));
		if(dist > 0){
			return dist;
		}else{
			return -1;
		}
	}
}

Color Light::shadeL(Ray& r, std::vector< std::shared_ptr< Figure > >& list, int& minC){
	r.setL(sqrt(	pow(*(getPos() + 0) - *(r.getPos() + 0), 2) +
			pow(*(getPos() + 1) - *(r.getPos() + 1), 2) +
			pow(*(getPos() + 2) - *(r.getPos() + 2), 2)));	//distance form r.pos to light
	for(int c = 0; c < list.size(); ++c){
		if(list[c] -> intersect(r) < r.getL() && list[c] -> intersect(r) > 0.1){
			return Black;
		}
	}

	float ref = 	*(list[minC]->getN(r.getPos()) + 0)**(r.getVec() + 0) +
			*(list[minC]->getN(r.getPos()) + 1)**(r.getVec() + 1) +
			*(list[minC]->getN(r.getPos()) + 2)**(r.getVec() + 2);	//Lambertian shading
	if(ref < 0){	//ref must be positive
		ref += -2*ref;
	}
	Color c(list[minC]->getCol().r, list[minC]->getCol().g, list[minC]->getCol().b);
	c *= ref;
	//c *= i;
	return c;
}

Color Light::shadeO(Ray& r, std::vector< std::shared_ptr< Figure > >& list, int& minC){

	Color c(list[minC]->getCol().r, list[minC]->getCol().g, list[minC]->getCol().b);
	return c;
}
