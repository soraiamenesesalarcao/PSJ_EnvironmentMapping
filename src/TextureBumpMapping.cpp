#include "TextureBumpMapping.h"

TextureBumpMapping::TextureBumpMapping(std::string file_textura,int texUnit, std::string file_normal, int texUnit2) : Texture(texUnit){
	int width, height, channels;

	_file_textura = file_textura;
	_file_normal = file_normal;

	_texID = std::vector<GLuint>(3);
	glGenTextures(2, &_texID[0]);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID[0]);

	unsigned char* image = SOIL_load_image(_file_textura.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	///----------------------------------------------
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _texID[1]);

	unsigned char* image2 = SOIL_load_image(_file_normal.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image2);
	SOIL_free_image_data(image2);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

TextureBumpMapping::~TextureBumpMapping() {
	glDeleteTextures(2, &_texID[0]);
}

void TextureBumpMapping::bind() {
	
	glBindTexture(GL_TEXTURE_2D, _MtexID[0]);
	glBindTexture(GL_TEXTURE_2D, _MtexID[1]);
}

void TextureBumpMapping::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBumpMapping::draw() {
	GLint tID = ShaderProgram::getInstance()->getTextureUniformId(TEX_2D);
	GLint t2ID = ShaderProgram::getInstance()->getTextureUniformId(TEX_NORMAL);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texID[0]);
	glUniform1i(tID, TEX_UNIT_0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _texID[1]);
	glUniform1i(t2ID, TEX_UNIT_1);
}