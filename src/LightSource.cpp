#include "LightSource.h"

LightSource::LightSource() {
}

void LightSource::setComponents(char* file, std::string lightID) {
	ConfigLoader::loadLight(file, lightID, &_position, &_ambient, &_diffuse, &_specular);
}

void LightSource::moveLeft(){
	_position.x += LIGHT_OFFSET;
}

void LightSource::moveRight(){
	_position.x -= LIGHT_OFFSET;
}

void LightSource::moveAhead(){
	_position.z += LIGHT_OFFSET;
}

void LightSource::moveBackwards(){
	_position.z -= LIGHT_OFFSET;
}

void LightSource::moveUp(){
	_position.y += LIGHT_OFFSET;
}

void LightSource::moveDown(){
	_position.y -= LIGHT_OFFSET;
}

void LightSource::draw(){
	// shader stuff here
}