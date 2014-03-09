#include "Texture2D.h"

Texture2D::Texture2D(std::string file, int texUnit) : Texture(texUnit) {
	int width, height, channels;

	_file = file;

	glGenTextures(1, &_texID);

	//glActiveTexture(GL_TEXTURE0);
	glActiveTexture(_texUnitEnum);
	glBindTexture(GL_TEXTURE_2D, _texID);

	unsigned char* image = SOIL_load_image(_file.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() {
	glBindTexture(GL_TEXTURE_2D, _texID);
}

void Texture2D::unbind() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::draw() {
	glActiveTexture(_texUnitEnum);
	bind();
	GLint tID = ShaderProgram::getInstance()->getTextureUniformId(TEX_2D);
	glUniform1i(tID, _texUnitInt);	
}

