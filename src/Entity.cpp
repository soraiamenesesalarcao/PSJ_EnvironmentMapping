#include "Entity.h"
#include "Utils.h"

Entity::Entity(std::string id){
		_id = id;
		_solid = 0;

/*	std::string texture;
	_height = _px = _py = _pz = 0.0;
	_reflection = reflection;
	_mesh = NULL;
	_texture = NULL;*/
}

Entity::~Entity(){
	//if(_mesh != NULL) _mesh->~Mesh();
	//if(_texture != NULL) _texture->~Texture();
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

	if(Input::getInstance()->keyWasReleased('T')) {
		_solid = (_solid + 1) % NSOLIDS;
	}
	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}

std::string Entity::getId(){
	return _id;
}

int Entity::getSolid(){
	return _solid;
}

