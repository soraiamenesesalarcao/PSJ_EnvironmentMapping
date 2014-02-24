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

void LightSource::moveUp(){
	_position.y += LIGHT_OFFSET;
}

void LightSource::moveDown(){
	_position.y -= LIGHT_OFFSET;
}

void LightSource::moveAhead(){
	_position.z += LIGHT_OFFSET;
}

void LightSource::moveBackwards(){
	_position.z -= LIGHT_OFFSET;
}


void LightSource::draw(){
	GLint positionId = ShaderProgram::getInstance()->getId("light_Position");
	GLint ambientId = ShaderProgram::getInstance()->getId("light_Ambient");
	GLint diffuseId = ShaderProgram::getInstance()->getId("light_Diffuse");
	GLint specularId = ShaderProgram::getInstance()->getId("light_Specular");

	glUniform3fv(positionId, 1, glm::value_ptr(_position));
	glUniform3fv(ambientId, 1, glm::value_ptr(_ambient));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuse));
	glUniform3fv(specularId, 1, glm::value_ptr(_specular));
}