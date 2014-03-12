#include "Entity.h"


const glm::vec3 Entity::DEFAULT_POSITION = glm::vec3(0,0,0);
const glm::quat Entity::DEFAULT_ROTATION = glm::quat();
const glm::vec3 Entity::DEFAULT_SCALE = glm::vec3(0.1,0.1,0.1);


Entity::Entity(std::string name){
	float x_angle = 0.0;
	_name = name;
	Properties initialProperty = { DEFAULT_POSITION, DEFAULT_ROTATION, DEFAULT_SCALE };
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
	_q = glm::angleAxis(x_angle, glm::vec3(1.0, 0.0, 0.0));
	_texture2D = NULL;
	_textureCube = NULL;
}

Entity::Entity(){
	_texture2D = NULL;
	_textureCube = NULL;
}


std::string Entity::getName() const{
	return _name;
}

/* read the .obj file*/
void Entity::setMesh(char * file){
	ConfigLoader::loadMesh(file, &_vertexArray);
}


void Entity::setMaterial(char* file){
	ConfigLoader::loadMaterial(file,  _ambientMaterial, _diffuseMaterial, _specularMaterial, _shininess);	
}


void Entity::setTexture2D(std::string file, int texUnit){
	_texture2D = new Texture2D(file, texUnit);	
}


void Entity::setTextureCube(std::string f1, std::string f2, std::string f3,
							std::string f4, std::string f5, std::string f6,
							int texUnit){
	_textureCube = new TextureCube(f1, f2, f3, f4, f5, f6, texUnit);
}

void Entity::cleanTextures() {
	if(_texture2D != NULL)
		_texture2D->~Texture2D();
	if(_textureCube != NULL)
		_textureCube->~TextureCube();
}

void Entity::rotate(glm::vec3 axis) {
	glm::quat q;
	float angle = ANGLE_OFFSET;
	if(angle > 360.0) angle -= 360.0;
	_q = glm::angleAxis(angle / ROTATION_DELAY, axis) * _propertiesArray[0].rotation;;
	_propertiesArray[0].rotation = _q;
	calculateModelMatrix();
	glutPostRedisplay();
}

void Entity::draw(int mode){

	calculateModelMatrix();
	calculateNormalMatrix();

	glBindVertexArray(_vaoId[0]);
	glUniformMatrix4fv(ShaderProgram::getInstance()->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniformMatrix3fv(ShaderProgram::getInstance()->getNormalMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentNormalMatrix));
	
	switch(mode) {
		case CUBE_MAPPING:
			_textureCube->draw();
			//_texture2D->draw();
			break;
		case SPHERE_MAPPING:
			_texture2D->draw();
			break;
		case BUMP_MAPPING:
			//_textureBumpMapping->draw();
			_texture2D->draw();
			break;
	}
	
	GLint ambientId = ShaderProgram::getInstance()->getId("MaterialAmbientColor");
	GLint diffuseId = ShaderProgram::getInstance()->getId("MaterialDiffuseColor");
	GLint specularId = ShaderProgram::getInstance()->getId("MaterialSpecularColor");
	GLint shininessId = ShaderProgram::getInstance()->getId("MaterialShininess");
	GLint illuminationId = ShaderProgram::getInstance()->getId("Illumination");

	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientMaterial));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseMaterial));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularMaterial));
	glUniform1f(shininessId, _shininess);
	glUniform1i(illuminationId, LIGHT_ON);

	glDrawArrays(GL_TRIANGLES, 0, _vertexArray.size());


	switch(mode) {
		case CUBE_MAPPING:
			_textureCube->unbind();
			//_texture2D->unbind();	
			break;
		case SPHERE_MAPPING:
			_texture2D->unbind();	
			break;
		case BUMP_MAPPING:
			//_textureBumpMapping->unbind();
			_texture2D->unbind();	
			break;
	}

	Utils::checkOpenGLError("ERROR: Could not draw Entity: " + _name);
}

void Entity::createBufferObjects(GLuint* vaoId, GLuint* vboId){
	_vaoId = vaoId;
	_vboId = vboId;
	glBindVertexArray(vaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, vboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*_vertexArray.size(), &_vertexArray[0], GL_STATIC_DRAW);
	//Vertex Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	//Vertex Normal
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].XYZW));
	//Vertex UV
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(_vertexArray[0].NORMAL)*2));
	//Vertex Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(_vertexArray[0].TANGENT));
}

void Entity::calculateModelMatrix(){
	glm::mat4 transformation1 = glm::scale(_propertiesArray[0].scale);
	glm::mat4 transformation2 = glm::toMat4(_propertiesArray[0].rotation);
	glm::mat4 transformation3 = glm::translate(_propertiesArray[0].position);
	_currentModelMatrix = transformation3 * transformation2 * transformation1 * glm::mat4();
}

void Entity::calculateNormalMatrix(){
	_currentNormalMatrix = glm::inverseTranspose(glm::mat3(Camera::getInstance()->getView()*_currentModelMatrix));
}

