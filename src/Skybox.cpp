#include "Skybox.h"


Skybox::Skybox() : Entity(){
	Properties initialProperty = { DEFAULT_POSITION, DEFAULT_ROTATION, glm::vec3(1.0, 1.0, 1.0)};
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
}

void Skybox::draw() {
	glBindVertexArray(_vaoId[0]);
	glUniformMatrix4fv(ShaderProgram::getInstance()->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniformMatrix3fv(ShaderProgram::getInstance()->getNormalMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentNormalMatrix));
	
	

	_textureCube->draw();

	GLint ambientId = ShaderProgram::getInstance()->getId("MaterialAmbientColor");
	GLint diffuseId = ShaderProgram::getInstance()->getId("MaterialDiffuseColor");
	GLint specularId = ShaderProgram::getInstance()->getId("MaterialSpecularColor");
	GLint shininessId = ShaderProgram::getInstance()->getId("MaterialShininess");
	GLint illuminationId = ShaderProgram::getInstance()->getId("Illumination");

	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientMaterial));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseMaterial));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularMaterial));
	glUniform1f(shininessId, _shininess);
	glUniform1i(illuminationId, LIGHT_OFF);

	glFrontFace(GL_CW);
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	glFrontFace(GL_CCW);

	_textureCube->unbind();
	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}