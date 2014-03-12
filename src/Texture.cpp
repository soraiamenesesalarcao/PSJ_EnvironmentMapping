#include "Texture.h"

Texture::Texture(int texUnit) {
	_texUnitInt = texUnit;

	if(_texUnitInt == TEX_UNIT_0)
		_texUnitEnum = GL_TEXTURE0;
	else if(_texUnitInt == TEX_UNIT_1)
		_texUnitEnum = GL_TEXTURE1;
	else if(_texUnitInt == TEX_UNIT_2)
		_texUnitEnum = GL_TEXTURE2;
}

//Texture::~Texture(){
//	glDeleteTextures(2, _texID);
//}