#ifndef SCENE_H
#define SCENE_H

#include "bitmap.h"
#include "figure.h"
#include "sphere.h"
#include "plane.h"
#include "light.h"

#include "assert.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>

class Scene{
	private:
		int x, y;	//dimensions in pixels
		Bitmap map(int x, int y);
		const char* inf;	//inputfile name for figs
		const char* inl;	//inputfile name for lights
		const char* out;	//outputfile name
		std::vector< std::shared_ptr< Figure > > figs;	//list of figure in scene
		std::vector< std::shared_ptr< Light > > lights;	//list of lights in scene
		std::vector< Color > bw;	//black and white image
		std::vector< Color > color;	//color image
		std::vector< Color > shading;	//color image with lambert shading
		
		std::string readType(std::fstream&);				//reads type of figure
		std::vector< int > readPos(std::fstream&);			//reads pos of fiugre
		std::vector< int > readSpeq(std::fstream&, std::string&);	//reads characteristics of figure
		std::vector< float > readCol(std::fstream&);			//reads color of fiugre
	public:
		Scene(int, int, const char*, const char*, const char*);
		int getX();
		int getY();
		const char* getInputf();
		const char* getInputl();
		const char* getOutput();
		void setFigs(const char*);
		void setLights(const char*);
		void printFigs();
		void printLights();
		void printDist(Ray&);
		Color setP(double, double, double, double, double, double);
		void render();
};

#endif
