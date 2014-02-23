#include "LightSource.h"

LightSource::LightSource() {
}

void LightSource::setComponents(char* file, std::string lightID) {
	ConfigLoader::loadLight(file, lightID, &_position, &_ambient, &_diffuse, &_specular);
}

void LightSource::moveLeft(){
	_position.x += LIGHT_OFFSET_X;
}

void LightSource::moveRight(){
	_position.x -= LIGHT_OFFSET_X;
}

void LightSource::draw(){
	// shader stuff here
}