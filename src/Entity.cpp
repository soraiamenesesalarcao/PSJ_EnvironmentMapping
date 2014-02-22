#include "Entity.h"
#include "Utils.h"

Entity::Entity(std::string id){
		_id = id;

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

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}

void Entity::update(){

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}

std::string Entity::getId(){
	return _id;
}

int Entity::getSolid(){
	return _solid;
}

void Entity::setSolid(int solid){
	_solid = solid;
}