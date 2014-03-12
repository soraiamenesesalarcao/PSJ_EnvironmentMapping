#include "Texturecube.h"

TextureCube::TextureCube(	std::string f1, std::string f2, std::string f3,
							std::string f4, std::string f5, std::string f6, 
							GLenum texUnit) : Texture(texUnit) {

	unsigned char* image;
	int width, height, channels;

	_files[0] = f1;
	_files[1] = f2;
	_files[2] = f3;
	_files[3] = f4;
	_files[4] = f5;
	_files[5] = f6;

	glGenTextures(1, &_texID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
	
	glActiveTexture(_texUnitEnum);

    for(int i = 0; i < 6; i++) {
		image = SOIL_load_image(_files[i].c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		SOIL_free_image_data(image);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

TextureCube::~TextureCube() {
	glDeleteTextures(1, &_texID);
}

void TextureCube::bind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
}

void TextureCube::unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void TextureCube::draw() {
	glActiveTexture(_texUnitEnum);
	bind();
	GLint tID = ShaderProgram::getInstance()->getTextureUniformId(TEX_CUBE);
	glUniform1i(tID, _texUnitInt);
}