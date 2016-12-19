#include "scene.h"

Scene::Scene(int width, int height, const char* infilef, const char* infilel, const char* outfile){
	x = width;
	y = height;
	inf = infilef;
	inl = infilel;
	out = outfile;
	bw.resize(x*y);
	color.resize(x*y);
	shading.resize(x*y);
}

int Scene::getX(){
	return x;
}

int Scene::getY(){
	return y;
}

const char* Scene::getInputf(){
	return inf;
}

const char* Scene::getInputl(){
	return inl;
}

const char* Scene::getOutput(){
	return out;
}


std::string Scene::readType(std::fstream& is){
	char colon = ':';
	std::string type;
	while(is.peek() != colon){
		char temp = is.peek();
		type += temp;
		assert(temp != '(');
		is >> temp;
	}
	assert(type == "sphere" || type == "plane");
	assert(is.peek() == colon); is >> colon;	//consume ':'
	return type;
}

std::vector< int > Scene::readPos(std::fstream& is){	//(x,y,z),
	char obracket = '(';
	char cbracket = ')';
	char comma = ',';
	assert(is.peek() == obracket); is >> obracket;	//consume (
	std::string input;
	std::vector< int > pos;
	for(int i = 0; i < 3; ++i){
		while(is.peek() != comma && is.peek() != cbracket){
			char temp = is.peek();
			input += temp;
			is >> temp;
		}
		pos.push_back(std::stoi(input));
		assert(pos[i] < 10000 && pos[i] > -10000);
		input.clear();
		if(is.peek() == comma){is >> comma;}	//consume ','
	}
	assert(is.peek() == cbracket); is >> cbracket;	//consume ')'
	assert(is.peek() == comma); is >> comma;	//consume ','
	return pos;
}

std::vector< int > Scene::readSpeq(std::fstream& is, std::string& type){	//(speqs,ref,op,tr),
	char obracket = '(';
	char cbracket = ')';
	char comma = ',';
	std::vector < int > speq;
	assert(is.peek() == obracket); is >> obracket;	//consume '('
	if(type == "sphere"){	//radius,ref,op,tr
		for(int i = 0; i < 4; ++i){
			std::string input;
			while(is.peek() != cbracket && is.peek() != comma){
				char temp = is.peek();
				input += temp;
				is >> temp;
			}
			speq.push_back(std::stoi(input));
			if(is.peek() == comma){is >> comma;}	//consume ','
		}
		assert(is.peek() == cbracket); is >> cbracket;	//consume ')'
		assert(is.peek() == comma); is >> comma;	//consume ','
		return speq;
	}else if(type == "plane"){	//x,y,z,ref,op,tr
		for(int i = 0; i < 6; ++i){
			std::string input;
			while(is.peek() != cbracket && is.peek() != comma){
				char temp = is.peek();
				input += temp;
				is >> temp;
			}
			speq.push_back(std::stoi(input));
			if(is.peek() == comma){is >> comma;}	//consume ','
		}
		assert(is.peek() == cbracket); is >> cbracket;	//consume ')'
		assert(is.peek() == comma); is >> comma;	//consume ','
		return speq;
	}else{
		std::cout << "memory read error, type not recognised\n";
	}
}

std::vector< float > Scene::readCol(std::fstream& is){
	char obracket = '(';
	char cbracket = ')';
	char comma = ',';
	char semicolon = ';';
	char newline = '\n';
	assert(is.peek() == obracket); is >> obracket;	//consume '('
	std::string input;
	std::vector< float > col;
	for(int i = 0; i < 3; ++i){
		while(is.peek() != comma && is.peek() != cbracket){
			char temp = is.peek();
			input += temp;
			is >> temp;
		}
		col.push_back(std::stof(input));
		assert(col[i] < 10000 && col[i] > -10000);
		input.clear();
		if(is.peek() == comma){is >> comma;}	//consume ','
	}
	assert(is.peek() == cbracket); is >> cbracket;	//consume ')'
	assert(is.peek() == semicolon);	is >> semicolon;	//consume ';'
	return col;
}

void Scene::setFigs(const char* filename){
	std::fstream is(filename);
	char end = '!';
	while(is.peek() != end){
		std::string type = readType(is);
		std::vector< int > pos = readPos(is);
		std::vector< int > speq = readSpeq(is, type);
		std::vector< float > col = readCol(is);
		if(type == "sphere"){
			figs.push_back(std::shared_ptr< Figure >(new Sphere(pos[0], pos[1], pos[2],
									speq[0],
									col[0], col[1], col[2],
									speq[1] != 0, speq[2] != 0, speq[3] != 0)));
		}else if(type == "plane"){
			figs.push_back(std::shared_ptr< Figure >(new Plane(pos[0], pos[1], pos[2],
									speq[0], speq[1], speq[2],
									col[0], col[1], col[2],
									speq[3] != 0, speq[4] != 0, speq[5] != 0)));
		}else{
			std::cout << "memory read error, unable to creat figure\n";
			break;
		}
	}
	std::cout << "figures imported\n";
}

void Scene::setLights(const char* filename){
	std::fstream is(filename);
	std::string in;
	char comma = ',';
	char endl = '\n';
	char semicolon = ';';
	char end = '!';
	/*
	while(std::getline(is, in)){
		vector< int > speq[4];
		while(in.peek() != semicolon){
			std::string input;
			while(in.peek() != comma && in.peek() != semicolon){
				char temp = in.peek();
				input += temp;
				in >> temp;
			}
			if(in.peek() == comma){
				in >> comma;
			}
			speq.push_back(std::stoi(input));
		}
		in >> semicolon;
		lights.push_back(std::shared_ptr< Light >(new Light (speq[0], speq[1], speq[2], speq[3])));
	}
	*/
	while(is.peek() != end){
		std::vector< int > speq;
		while(is.peek() != semicolon){
			for(int i = 0; i < 4; ++i){
				std::string input;
				while(is.peek() != comma && is.peek() != semicolon){
					char temp = is.peek();
					input += temp;
					is >> temp;
				}
				if(is.peek() == comma){
					is >> comma;
				}
				speq.push_back(std::stoi(input));
			}

		}
		is >> semicolon;
		lights.push_back(std::shared_ptr< Light >(new Light (speq[0], speq[1], speq[2], speq[3])));
	}
	std::cout << "lights imported\n";
}

void Scene::printFigs(){
	std::cout << "number of figures in scene: " << figs.size() << "\n";
	for(int i = 0; i < figs.size(); ++i){
		std::string type = typeid(*figs[i]).name();
		type.erase(0, 1);
		std::cout << type << ":\t" << *figs[i]->getPos() << "\t"
			<< *(figs[i]->getPos() + 1) << "\t"
			<< *(figs[i]->getPos() + 2) << "\t; ";
		std::cout << figs[i]->getCol().r << "\t"
			<< figs[i]->getCol().g << "\t"
			<< figs[i]->getCol().b << "\n";
	}
}

void Scene::printLights(){
	std::cout << "number of lights in scene: " << lights.size() << "\n";
	for(int i = 0; i < lights.size(); ++i){
		std::cout << *lights[i]->getPos() << ", \t"
			<< *(lights[i]->getPos() + 1) << ", \t"
			<< *(lights[i]->getPos() + 2) << "; "
			<< lights[i]->getL() << "\n";
	}
}

void Scene::printDist(Ray& r){
	std::cout << "Ray at: ";
	std::cout << *r.getPos() << ", " << *(r.getPos() + 1) << ", " << *(r.getPos() + 2) << "\n";
	for(int i = 0; i < figs.size(); ++i){
		std::cout << *figs[i]->getPos() << ",\t"
			<< *(figs[i]->getPos() + 1) << ",\t"
			<< *(figs[i]->getPos() + 2) << "\t: ";
		std::cout << figs[i]->intersect(r) << "\n";
	}
}

Color Scene::setP(double x0, double y0, double z0, double vx, double vy, double vz){
	Ray r(x0, y0, z0, vx, vy, vz);		//sight ray
	double minDist = INFINITY;		//distance to closest figure
	int minC = -1;				//index of closest figure
	for(int c = 0; c < figs.size(); ++c){	//finds figure closest to ray origin
		if(figs[c]->intersect(r) <= minDist && figs[c]->intersect(r) > 0){
			minC = c;
			minDist = figs[c]->intersect(r);
		}
	}
	if(minC != -1){	//ray intersects figs[minC]
		if(figs[minC]->getReflective()){	//nearest figure is reflective => return setP of reflection
			double R = 2 * (*figs[minC]->getN(r) * *r.getVec() +
				*(figs[minC]->getN(r) + 1) * *(r.getVec() + 1) +
				*(figs[minC]->getN(r) + 2) * *(r.getVec() + 2));	//2 (n * v)
			return setP(*r.getVec() * minDist + *r.getPos(),
				*(r.getVec() + 1) * minDist + *(r.getPos() + 1),
				*(r.getVec() + 2) * minDist + *(r.getPos() + 2),	//vec * dist + pos
				-R * *figs[minC]->getN(r) + *r.getVec() + *r.getPos() + *r.getVec() * minDist,
				-R * *(figs[minC]->getN(r) + 1) + *(r.getVec() + 1) + *(r.getPos() + 1) + *(r.getVec() + 1) * minDist,
				-R * *(figs[minC]->getN(r) + 2) + *(r.getVec() + 2) + *(r.getPos() + 2) + *(r.getVec() + 2) * minDist);	//vec - 2 (vec * n) n + v * dist + pos
		}else if(figs[minC]->getTranslucent()){	//nearest figure is translucent => return setP of refraction

		}else{	//nearest fig is opaque => return Color
			Color col = Black;
			for(int a = 0; a < lights.size(); ++a){
				Ray rl(	*(0 + r.getVec()) * minDist + *(0 + r.getPos()),
					*(1 + r.getVec()) * minDist + *(1 + r.getPos()),
					*(2 + r.getVec()) * minDist + *(2 + r.getPos()),
					*(lights[a]->getPos() + 0),
					*(lights[a]->getPos() + 1),
					*(lights[a]->getPos() + 2));	//light ray
				col += lights[a]->shadeL(rl, figs, minC);	//add lambert shading to col
			}
			return col;
		}
	}else{	//ray does not intersect any figure
		return Black;
	}
}


void Scene::render(){
	Bitmap bitmap(x, y);

	Ray r (-y, 0, 0, 0, 0, 0);	//sight ray
	Ray rl(1, 0, 0,1, 0, 0);	//light ray
	bitmap.Fill(Black);

	for(int i = -y/2; i < y/2; ++i){	//lines
		for(int j = -x/2; j < x/2; ++j){	//colums
			bitmap(j + x/2, i + y/2) += setP(-y, 0, 0, 0, j + 0.5, i + 0.5);
		}

	}
	bitmap.Save(out);
}
