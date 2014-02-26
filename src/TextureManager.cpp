#include "TextureManager.h"
#include "SOIL.h"

const GLuint TextureManager::FIRE = 0;
const GLuint TextureManager::STONE = 1;

TextureManager* TextureManager::_inst(0);

TextureManager* TextureManager::Inst()
{
	if(!_inst)
		_inst = new TextureManager();

	return _inst;
}

TextureManager::TextureManager(){
	_texID = std::vector<GLuint>(2);
	glGenTextures(2, &_texID[0]); 
	loadTexture("../scripts/textures/fire.tga", FIRE);
	loadTexture("../scripts/textures/stone.tga", STONE); 
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