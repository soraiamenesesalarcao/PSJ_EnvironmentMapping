#pragma once

#include "Utils.h"
#include "Definitions.h"


class ShaderProgram {

	private:
		glm::vec3 _activeProgram;
		std::vector<glm::vec3> _programId;
		int compileShader(char * shaderFile, int shaderType);
		ShaderProgram();

		GLuint _modelMatrixUniformId;
		GLuint _normalMatrixUniformId;
		GLuint _sharedMatrixUboId;
		GLuint _textureUniformId[3];


	public:
		static ShaderProgram * getInstance();
		int createShaderProgram(char * vSFile, char * fSFile);
		void destroyShaderProgram();
		const GLuint getUId(std::string key);
		const GLint getId(std::string key);
		void bind(GLuint id);
		void unBind();

		GLuint getModelMatrixUniformId() const  { return _modelMatrixUniformId; }
		GLuint getNormalMatrixUniformId() const  { return _normalMatrixUniformId; }
		GLuint getSharedMatrixUboId() const { return _sharedMatrixUboId; }
		GLuint getTextureUniformId(int index) const  { return _textureUniformId[index]; }
};