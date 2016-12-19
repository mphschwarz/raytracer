#include <iostream>
#include <fstream>

#include "scene.h"

int main(){
	Scene s(1024, 1024, "figuresIn", "lightsIn", "scene.bmp");
	s.setFigs("figuresIn");
	s.setLights("lightsIn");
	s.printFigs();
	s.printLights();
	/*
	Ray r(0, 0, 0, 40, 0, 0);
	std::vector< std::shared_ptr< Figure > > list;
	Sphere sp(40, 0, 0, 20);
	list.push_back(std::shared_ptr< Figure >(new Sphere (40, 0, 0, 20)));
	std::cout << *list[0]->getN(r) << ", " << *(list[0]->getN(r) + 1) << ", " << *(list[0]->getN(r) + 2) << "\n";
	*/
	s.render();
	return 0;
}
