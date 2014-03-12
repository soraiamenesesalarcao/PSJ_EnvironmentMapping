#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(){}


ShaderProgram * ShaderProgram::getInstance(){
	static ShaderProgram instance;
	return &instance;
}

int ShaderProgram::compileShader(char * shaderFile, int shaderType){
	const char* shader = Utils::readFile(shaderFile);
	int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &shader, 0);
	glCompileShader(shaderId);
	return shaderId;
}

int ShaderProgram::createShaderProgram(char * vSFile, char * fSFile){
	GLuint vertexShaderId = compileShader(vSFile, GL_VERTEX_SHADER);
	GLuint fragmentShaderId = compileShader(fSFile, GL_FRAGMENT_SHADER);
	GLuint id = glCreateProgram();

	glm::vec3 program;
	program.x = id;
	program.y = vertexShaderId;
	program.z = fragmentShaderId;
	_programId.push_back(program);

	glAttachShader(id, vertexShaderId);
	glAttachShader(id, fragmentShaderId);
	glBindAttribLocation(id, VERTICES, "in_Position");
	glBindAttribLocation(id, NORMALS, "in_Normal");
	glBindAttribLocation(id, UVS, "in_UV");
	glBindAttribLocation(id, TANGENTS, "in_Tangent");
	glLinkProgram(id);
	
	_modelMatrixUniformId = glGetUniformLocation(id, "ModelMatrix");
	_normalMatrixUniformId = glGetUniformLocation(id, "NormalMatrix");
	_sharedMatrixUboId = glGetUniformBlockIndex(id, "SharedMatrices");	

	_textureUniformId[TEX_2D] = glGetUniformLocation(id, "Texture2D");
	_textureUniformId[TEX_CUBE] = glGetUniformLocation(id, "CubeMap");
	_textureUniformId[TEX_NORMAL] = glGetUniformLocation(id, "NormalTexture");

	glUniformBlockBinding(id, glGetUniformBlockIndex(id, "SharedMatrices"), 0);

	Utils::checkOpenGLError("ERROR: Could not create shaders.");

	return id;
}

void ShaderProgram::destroyShaderProgram(){
	for(std::vector<glm::vec3>::iterator iterator = _programId.begin(); iterator < _programId.end(); iterator++){
		glUseProgram(iterator->x);
		glDetachShader(iterator->x, iterator->y);
		glDetachShader(iterator->x, iterator->z);
		glDeleteShader(iterator->y);
		glDeleteShader( iterator->z);
		glDeleteProgram(iterator->x);
	}
	Utils::checkOpenGLError("ERROR: Could not destroy shaders.");
}

const GLuint ShaderProgram::getUId(std::string key) {
	if(key.compare("Program") == 0) return _activeProgram.x;
	if(key.compare("VertexShader") == 0) return _activeProgram.y;
	if(key.compare("FragmentShader") == 0) return _activeProgram.z;
}

const GLint ShaderProgram::getId(std::string key) {
	return glGetUniformLocation(_activeProgram.x, key.c_str());
}

void ShaderProgram::bind(GLuint id){
	glm::vec3 program;
	for(std::vector<glm::vec3>::iterator iterator = _programId.begin(); iterator < _programId.end(); iterator++){
		if(iterator->x == id)
			program = *iterator;
	}
	_activeProgram = program;
	glUseProgram(_activeProgram.x);
}

void ShaderProgram::unBind(){
	_activeProgram = glm::vec3();
	glUseProgram(0);
}