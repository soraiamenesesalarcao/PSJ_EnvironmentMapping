#include "Entity.h"
#include "Utils.h"


Entity::Entity(int solid){
	//	_id = id;
		_solid = solid;
	//	_matID = matID;
}

Entity::Entity(){
	//	_id = id;
		_solid = CUBE;
	//	_matID = "ruby";
}


void Entity::init() {

}

void Entity::draw(){

	if(_solid == CUBE) {
		// desenhar cubo
	}
	else {
		// desenhar teapot
	}

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}

void Entity::update(){	

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}

/* std::string Entity::getId(){
	return _id;
} */

int Entity::getSolid(){
	return _solid;
}

void Entity::changeSolid(){
	_solid = (_solid + 1) % NSOLIDS;
}


void Entity::setMaterial(char* file, std::string matID){
	//_matID = matID;

	ConfigLoader::loadMaterial(file, matID, &_ambientMaterial, &_diffuseMaterial, &_specularMaterial, &_shininess);
}

