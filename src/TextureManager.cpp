#include "TextureManager.h"

TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst() {
	if(!_inst) _inst = new TextureManager();
	return _inst;
}

TextureManager::TextureManager(){
	_texID = std::vector<GLuint>(2);
	glGenTextures(2, &_texID[0]);
	loadTexture("textures/stone.tga", TEX_STONE);
	loadTextureCube("textures/negx.jpg", "textures/negy.jpg", 
					"textures/negz.jpg", "textures/posx.jpg",
					"textures/posy.jpg", "textures/posz.jpg",
					TEX_ENV_CUBE);
}

void TextureManager::loadTexture(const char* dirName, int textID){
	int width, height;
	int channel;
	unsigned char* image = SOIL_load_image(dirName, &width, &height, &channel, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, _texID[textID]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering (optional)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering (optional)
	SOIL_free_image_data(image);
}

void TextureManager::loadTextureCube(const char* dirNameNX, const char* dirNameNY, 
									 const char* dirNameNZ, const char* dirNamePX, 
									 const char* dirNamePY, const char* dirNamePZ,
									 int textID){

	unsigned char* image;
	int width, height;
	int channel;
	const char* images[6] = {dirNamePX, dirNameNX, dirNamePY, dirNameNY, dirNamePZ, dirNameNZ};

	glBindTexture(GL_TEXTURE_CUBE_MAP, _texID[textID]);

	// Load Cube Map images
    for(int i = 0; i < 6; i++) {
        image = SOIL_load_image(images[i], &width, &height, &channel, SOIL_LOAD_RGB);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        SOIL_free_image_data(image);
	}
}
	
TextureManager::~TextureManager(){
	UnloadAllTextures();
	_inst = 0;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(texID < _texID.size()){
		if(texID != TEX_ENV_CUBE) glBindTexture(GL_TEXTURE_2D, _texID[texID]);
		else glBindTexture(GL_TEXTURE_CUBE_MAP, _texID[texID]);
	}
	else result = false;	//otherwise, binding failed

	return result;
}


bool TextureManager::UnloadTexture(const unsigned int texID){
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the vector
	if(texID < _texID.size()){
		glDeleteTextures(1, &(_texID[texID]));
		_texID.erase(_texID.begin()+texID);
	}
	//otherwise, unload failed
	else {
		result = false;
	}

	return result;
}

void TextureManager::UnloadAllTextures(){
	while(!_texID.empty())
		UnloadTexture(0);
}