#include "Entity.h"
#include "Utils.h"


Entity::Entity(int solid){
		_solid = solid;
}


Entity::Entity(){
		_solid = CUBE;
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


int Entity::getSolid(){
	return _solid;
}


void Entity::changeSolid(){
	_solid = (_solid + 1) % NSOLIDS;
}


void Entity::setMaterial(char* file, std::string matID){
	ConfigLoader::loadMaterial(file, matID, &_ambientMaterial, &_diffuseMaterial, &_specularMaterial, &_shininess);

	// DEBUG
	std::cout << "Ambient: [ " << _ambientMaterial.r << " " << _ambientMaterial.g << " " << _ambientMaterial.b << " ]" << std::endl;
 }

