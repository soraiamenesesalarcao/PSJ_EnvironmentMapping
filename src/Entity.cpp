#include "Entity.h"
#include "Utils.h"


Entity::Entity(std::string matID){
	//	_id = id;
		_solid = CUBE;
		_matID = matID;
}

Entity::Entity(){
	//	_id = id;
		_solid = CUBE;
		_matID = "ruby";
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

std::string Entity::getMaterial(){
	return _matID;
}

void Entity::setMaterial(std::string matID){
	_matID = matID;
}

