#include "LightSource.h"

LightSource::LightSource() {
}

void LightSource::setComponents(char* file, std::string lightID) {
	ConfigLoader::loadLight(file, lightID, &_position, &_ambient, &_diffuse, &_specular, &_attenuation);
}

void LightSource::incX(){
	_position.x += LIGHT_OFFSET;
}

void LightSource::decX(){
	_position.x -= LIGHT_OFFSET;
}

void LightSource::incY(){
	_position.y += LIGHT_OFFSET;
}

void LightSource::decY(){
	_position.y -= LIGHT_OFFSET;
}

void LightSource::incZ(){
	_position.z += LIGHT_OFFSET;
}

void LightSource::decZ(){
	_position.z -= LIGHT_OFFSET;
}


void LightSource::draw(){
	GLint positionId = ShaderProgram::getInstance()->getId("LightPosition");
	GLint ambientId = ShaderProgram::getInstance()->getId("LightAmbient");
	GLint diffuseId = ShaderProgram::getInstance()->getId("LightDiffuse");
	GLint specularId = ShaderProgram::getInstance()->getId("LightSpecular");
	GLint linearAttenuationId = ShaderProgram::getInstance()->getId("LightLinearAttenuation");
	GLint quadraticAttenuationId = ShaderProgram::getInstance()->getId("LightQuadraticAttenuation");
	GLint cubicAttenuationId = ShaderProgram::getInstance()->getId("LightCubicAttenuation");

	std::cout << "Light: Attenuation: [ " << _attenuation[0] << " " << _attenuation[1] << " " << _attenuation[2] << " ]" << std::endl;

	glUniform3fv(positionId, 1, glm::value_ptr(_position));
	glUniform3fv(ambientId, 1, glm::value_ptr(_ambient));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuse));
	glUniform3fv(specularId, 1, glm::value_ptr(_specular));

	glUniform1f(linearAttenuationId, _attenuation[0]);
	glUniform1f(quadraticAttenuationId, _attenuation[1]);
	glUniform1f(cubicAttenuationId,_attenuation[2]);

}