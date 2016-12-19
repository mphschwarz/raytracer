#ifndef RAY_H
#define RAY_H

class Ray{
	private:
		double pos[3];
		double vec[3];
		double length;
	public:
		Ray(double x,  double y, double z, double X, double Y, double Z);
		Ray();
		double* getPos();
		double* getVec();
		double& getL();
		void setPos(double x, double y, double z);
		void setVec(double x, double y, double z);
		void setL(double);
  		double* crossp(Ray&);
  		double dotp(Ray&);
};

#endif
