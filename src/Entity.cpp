#include "Entity.h"
#include "Utils.h"

#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/intersect.hpp>

using namespace glm;

const vec3 Entity::DEFAULT_POSITION = vec3(0,0,0);
const quat Entity::DEFAULT_ROTATION = quat();
const vec3 Entity::DEFAULT_SCALE = vec3(0.1,0.1,0.1);

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
	mat4 transformation1 = glm::scale(_propertiesArray[0].scale);
	mat4 transformation2 = glm::toMat4(_propertiesArray[0].rotation);
	mat4 transformation3 = glm::translate(_propertiesArray[0].position);
	_currentModelMatrix = transformation3 * transformation2 * transformation1 * mat4();
}

void Entity::calculateNormalMatrix(){
	// TO DO: figure this out
	//_currentNormalMatrix = glm::inverseTranspose(Camera::getInstance()->getView()*_currentModelMatrix);
	_currentNormalMatrix = _currentModelMatrix;
}

void Entity::setVaoId(int value){
	_vaoId = value;
}

void Entity::setVboId(int value){
	_vboId = value;
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
	loadMesh(fileName.c_str());
}

std::string Entity::getObjFileDir(){
	return _objFileDir;
}


void Entity::draw(GLuint* vaoId, GLuint programId, GLuint programNormalId, GLuint programTextureId){

	glBindVertexArray(vaoId[0]);
	glUniformMatrix4fv(programId, 1, GL_FALSE, glm::value_ptr(_currentModelMatrix));
	glUniformMatrix4fv(programNormalId, 1, GL_FALSE, glm::value_ptr(_currentNormalMatrix));
	
	glActiveTexture(GL_TEXTURE0);
	TextureManager::Inst()->BindTexture(1);
	glUniform1i(programTextureId, 0);
	
	glActiveTexture(GL_TEXTURE1);
	TextureManager::Inst()->BindTexture(0);
	glUniform1i(programTextureId, 1);

	std::cout << "Material ambient: [ " << _ambientMaterial.r << " " << _ambientMaterial.g << " " << _ambientMaterial.b << " ]" << std::endl;

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

void Entity::loadMesh(const char* fileName){
        std::string line = std::string();
        std::ifstream file(fileName);

		//Temporary arrays to store loaded information
        std::vector<glm::vec4> vertices, normals;
		std::vector<glm::vec2> uvs;
        
        if (file.is_open()) {
                while (getline(file, line)) {
					std::vector<std::string> splitedLine = explode(line, ' ');
					if(splitedLine.size() > 0){
						if(splitedLine[0] == "#"){
							continue; //Comment in obj, skip this line
						}
						else if(splitedLine[0] == "v"){ //Ex line => v 1.00000 0.45555 1.10000
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							vertices.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "vt"){ //Ex line => vt 1.00000 0.45555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							uvs.push_back(glm::vec2(x,y));
						}
						else if(splitedLine[0] == "vn"){ //Ex line => vn 1.00000 0.45555 0.65555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							normals.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "f"){ 
							Vertex vertex1, vertex2, vertex3;
							std::vector<std::string> face1 = explode(splitedLine[1], '/');
							std::vector<std::string> face2 = explode(splitedLine[2], '/');
							std::vector<std::string> face3 = explode(splitedLine[3], '/');
							//Copy vertex information from temporary vertices array to vertices
							memcpy(vertex1.XYZW, &vertices[atoi(face1[0].c_str())-1][0], sizeof(vertex1.XYZW));
							memcpy(vertex2.XYZW, &vertices[atoi(face2[0].c_str())-1][0], sizeof(vertex2.XYZW));
							memcpy(vertex3.XYZW, &vertices[atoi(face3[0].c_str())-1][0], sizeof(vertex3.XYZW));
							if((face1.size() > 1) && face1[1].size() > 0){
								//UV information
								memcpy(vertex1.UV, &uvs[atoi(face1[1].c_str())-1][0], sizeof(vertex1.UV));
								memcpy(vertex2.UV, &uvs[atoi(face2[1].c_str())-1][0], sizeof(vertex2.UV));
								memcpy(vertex3.UV, &uvs[atoi(face3[1].c_str())-1][0], sizeof(vertex3.UV));
							}
							if((face1.size() > 2) && face1[2].size() > 0){
								//Normal information
								memcpy(vertex1.NORMAL, &normals[atoi(face1[2].c_str())-1][0], sizeof(vertex1.NORMAL));
								memcpy(vertex2.NORMAL, &normals[atoi(face2[2].c_str())-1][0], sizeof(vertex2.NORMAL));
								memcpy(vertex3.NORMAL, &normals[atoi(face3[2].c_str())-1][0], sizeof(vertex3.NORMAL));
							}
							_vertexArray.push_back(vertex1);
							_vertexArray.push_back(vertex2);
							_vertexArray.push_back(vertex3);
						}
					}
                }
        }
        else{
			std::cerr << "Cannot open " << fileName << std::endl; exit(1);
		}
}


std::vector<std::string> Entity::explode(const std::string &s, char delim){
	int i = 0;
	std::vector<std::string> result;
    std::istringstream iss(s);
    for (std::string token; std::getline(iss, token, delim);)
		result.push_back(token);
	return result;
}

