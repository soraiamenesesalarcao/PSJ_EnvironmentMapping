#include "TextureManager.h"


const GLuint TextureManager::FIRE = 0;
const GLuint TextureManager::STONE = 1;
const GLuint TextureManager::ENV_CUBE = 2;
 
TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst() {
	if(!_inst) _inst = new TextureManager();
	return _inst;
}

TextureManager::TextureManager(){
	_texID = std::vector<GLuint>(3);
	glGenTextures(3, &_texID[0]);
	loadTexture("textures/negx.jpg", STONE); 
	loadTexture("textures/fire.tga", FIRE);
	loadTextureCube("textures/negx.jpg", "textures/negy.jpg", 
					"textures/negz.jpg", "textures/posx.jpg",
					"textures/posy.jpg", "textures/posz.jpg",
					ENV_CUBE);
}

void TextureManager::loadTexture(const char* dirName, int textID){
	int width, height;
	int channel;
	unsigned char* image = SOIL_load_image(dirName, &width, &height, &channel, SOIL_LOAD_RGB);
	glBindTexture(GL_TEXTURE_2D, _texID[textID]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, image);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // Linear Filtering (optional)
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // Linear Filtering (optional)
	SOIL_free_image_data(image);
}

void TextureManager::loadTextureCube(const char* dirNameNX, const char* dirNameNY, 
									 const char* dirNameNZ, const char* dirNamePX, 
									 const char* dirNamePY, const char* dirNamePZ,
									 int textID){

	GLuint image = SOIL_load_OGL_cubemap(dirNamePX, dirNameNX, dirNamePY, 
										 dirNameNY, dirNamePZ, dirNameNZ,
										 SOIL_LOAD_RGB, 
										 SOIL_CREATE_NEW_ID, 0);


	//glBindTexture(GL_TEXTURE_CUBE_MAP, _texID[textID]);
	//glBindTexture(GL_TEXTURE_CUBE_MAP, image);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

//these should never be called
//TextureManager::TextureManager(const TextureManager& tm){}
//TextureManager& TextureManager::operator=(const TextureManager& tm){}
	
TextureManager::~TextureManager(){
	UnloadAllTextures();
	_inst = 0;
}

bool TextureManager::LoadTexture(const char* filename, const unsigned int texID, GLenum image_format, GLint internal_format, GLint level, GLint border) {
	//Not implemented
	return false;
}

bool TextureManager::UnloadTexture(const unsigned int texID){
	bool result(true);
	//if this texture ID mapped, unload it's texture, and remove it from the vector
	if(texID < _texID.size()){
		glDeleteTextures(1, &(_texID[texID]));
		_texID.erase(_texID.begin()+texID);
	}
	//otherwise, unload failed
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(const unsigned int texID)
{
	bool result(true);
	//if this texture ID mapped, bind it's texture as current
	if(texID < _texID.size())
		glBindTexture(GL_TEXTURE_2D, _texID[texID]);
	//otherwise, binding failed
	else
		result = false;

	return result;
}

void TextureManager::UnloadAllTextures(){
	while(!_texID.empty())
		UnloadTexture(0);
}