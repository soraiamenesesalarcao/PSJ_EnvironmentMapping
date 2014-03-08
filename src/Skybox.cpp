#include "Skybox.h"


Skybox::Skybox() : Entity(){

}

void Skybox::draw() {
	glBindVertexArray(_vaoId[0]);
	glUniformMatrix4fv(ShaderProgram::getInstance()->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniformMatrix4fv(ShaderProgram::getInstance()->getNormalMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentNormalMatrix));
	
	//glActiveTexture(GL_TEXTURE0);
	/*TextureManager::Inst()->BindTexture(TEX_FIRE); 
	glUniform1i(ShaderProgram::getInstance()->getTextureUniformId(), 0);
	//std::cout << "GL_TEXTURE0: " << GL_TEXTURE0 << std::endl;*/
	
	//TextureManager::Inst()->BindTexture(TEX_STONE);
	//glUniform1i(ShaderProgram::getInstance()->getTextureUniformId(), 1);

	//TextureManager::Inst()->BindTexture(TEX_ENV_CUBE);
	//glUniform1i(ShaderProgram::getInstance()->getTextureUniformId(), 0);

	GLint ambientId = ShaderProgram::getInstance()->getId("MaterialAmbientColor");
	GLint diffuseId = ShaderProgram::getInstance()->getId("MaterialDiffuseColor");
	GLint specularId = ShaderProgram::getInstance()->getId("MaterialSpecularColor");
	GLint shininessId = ShaderProgram::getInstance()->getId("MaterialShininess");

	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientMaterial));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseMaterial));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularMaterial));
	glUniform1f(shininessId, _shininess);

	glFrontFace(GL_CW);
	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	glFrontFace(GL_CCW);
	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}