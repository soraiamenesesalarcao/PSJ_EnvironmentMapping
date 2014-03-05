#include "Entity.h"


const glm::vec3 Entity::DEFAULT_POSITION = glm::vec3(0,0,0);
const glm::quat Entity::DEFAULT_ROTATION = glm::quat();
const glm::vec3 Entity::DEFAULT_SCALE = glm::vec3(0.1,0.1,0.1);

float x_angle = 0.0;
float y_angle = 0.0;
float z_angle = 0.0;

Entity::Entity(int solid, std::string name) : _textureID(-1){
	_name = name;
	_solid = solid;
	Properties initialProperty = { DEFAULT_POSITION, DEFAULT_ROTATION, DEFAULT_SCALE };
	_propertiesArray.push_back(initialProperty);
	calculateModelMatrix();
	calculateNormalMatrix();
	_q = glm::angleAxis(x_angle, glm::vec3(1,0,0));
}

void Entity::calculateModelMatrix(){
	glm::mat4 transformation1 = glm::scale(_propertiesArray[0].scale);
	glm::mat4 transformation2 = glm::toMat4(_propertiesArray[0].rotation);
	glm::mat4 transformation3 = glm::translate(_propertiesArray[0].position);
	_currentModelMatrix = transformation3 * transformation2 * transformation1 * glm::mat4();
}

void Entity::calculateNormalMatrix(){
	// TO DO: figure this out
	//_currentNormalMatrix = glm::inverseTranspose(Camera::getInstance()->getView()*_currentModelMatrix);
	_currentNormalMatrix = _currentModelMatrix;
}


std::string Entity::getName() const{
	return _name;
}

void Entity::setTexture(const int id){
	_textureID = id;
}

void Entity::setColor(const float color[4]){
	memcpy(_color, color, sizeof(float)*4);
}

void Entity::setColor(const float r, const float g, const float b, const float a){
	_color[0] = r;
	_color[1] = g;
	_color[2] = b;
	_color[3] = a;
}

/* read the .obj file*/
void Entity::setObjEntity(std::string fileName){
	_objFileDir = fileName;
	setColor(1.0f, 0.0f, 0.0f, 1.0f);
	//_textureID = textureID;
	ConfigLoader::loadMesh(fileName.c_str(), &_vertexArray);
}

std::string Entity::getObjFileDir(){
	return _objFileDir;
}


void Entity::draw(){

	glBindVertexArray(_vaoId[0]);
	glUniformMatrix4fv(ShaderProgram::getInstance()->getModelMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniformMatrix4fv(ShaderProgram::getInstance()->getNormalMatrixUniformId(), 1, GL_FALSE, glm::value_ptr(_currentNormalMatrix));
	
	glActiveTexture(GL_TEXTURE0);
	TextureManager::Inst()->BindTexture(1);
	glUniform1i(ShaderProgram::getInstance()->getTextureUniformId(), 0);
	
	glActiveTexture(GL_TEXTURE1);
	TextureManager::Inst()->BindTexture(0);
	glUniform1i(ShaderProgram::getInstance()->getTextureUniformId(), 1);

	GLint ambientId = ShaderProgram::getInstance()->getId("MaterialAmbientColor");
	GLint diffuseId = ShaderProgram::getInstance()->getId("MaterialDiffuseColor");
	GLint specularId = ShaderProgram::getInstance()->getId("MaterialSpecularColor");
	GLint shininessId = ShaderProgram::getInstance()->getId("MaterialShininess");

	glUniform3fv(ambientId, 1, glm::value_ptr(_ambientMaterial));
	glUniform3fv(diffuseId, 1, glm::value_ptr(_diffuseMaterial));
	glUniform3fv(specularId, 1, glm::value_ptr(_specularMaterial));
	glUniform1f(shininessId, _shininess);

	glDrawArrays(GL_TRIANGLES,0,_vertexArray.size());
	Utils::checkOpenGLError("ERROR: Could not draw scene.");
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
}

void Entity::update(){	
	glm::quat q;

	if(Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON)){ //x 
		x_angle += 0.05;
		if( x_angle > 360.0 ) x_angle -= 360.0;
		_q = glm::angleAxis(x_angle / ROTATION_SPEED, glm::vec3(1,0,0)) * _propertiesArray[0].rotation;;
		_propertiesArray[0].rotation = _q;
		calculateModelMatrix();
		calculateNormalMatrix();
		glutPostRedisplay();
	}
	if(Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON)){ //y
		y_angle += 0.05;
		if( y_angle > 360.0 ) y_angle -= 360.0;
		_q = glm::angleAxis(y_angle / ROTATION_SPEED, glm::vec3(0,1,0)) * _propertiesArray[0].rotation;
		_propertiesArray[0].rotation = _q;
		calculateModelMatrix();
		calculateNormalMatrix();
		glutPostRedisplay();
	}
	if(Input::getInstance()->mouseWasPressed(GLUT_MIDDLE_BUTTON)){ //z
		z_angle += 0.05;
		if( z_angle > 360.0 ) z_angle -= 360.0;
		_q = glm::angleAxis(z_angle / ROTATION_SPEED, glm::vec3(0,0,1)) * _propertiesArray[0].rotation;
		_propertiesArray[0].rotation = _q;
		calculateModelMatrix();
		calculateNormalMatrix();
		glutPostRedisplay();
	}

	if(Input::getInstance()->keyWasReleased('R')){
		x_angle = 0.0; 
		y_angle = 0.0;
		z_angle = 0.0;
		_q = glm::angleAxis(x_angle, glm::vec3(1,1,1));
		_propertiesArray[0].rotation = _q;
		calculateModelMatrix();
		calculateNormalMatrix();
	}

	Utils::checkOpenGLError("ERROR: Could not draw scene.");
}


int Entity::getSolid(){
	return _solid;
}


void Entity::changeSolid(){
	_solid = (_solid + 1) % NSOLIDS;
}


void Entity::setMaterial(char* file){
	ConfigLoader::loadMaterial(file,  _ambientMaterial, _diffuseMaterial, _specularMaterial, _shininess);	
}




