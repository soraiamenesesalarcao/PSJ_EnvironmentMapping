#include "Texturecube.h"

TextureCube::TextureCube(	std::string f1, std::string f2, std::string f3,
							std::string f4, std::string f5, std::string f6, 
							GLenum texUnit) : Texture(texUnit) {
	_files[0] = f1;
	_files[1] = f2;
	_files[2] = f3;
	_files[3] = f4;
	_files[4] = f5;
	_files[5] = f6;

	// cenas fixes irao acontecer aqui
}

void TextureCube::bind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID);
}

void TextureCube::unbind() {
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}