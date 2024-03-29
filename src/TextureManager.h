#pragma once

#include "Definitions.h"


class TextureManager {

	public:
		static TextureManager* Inst();
		virtual ~TextureManager();

		bool LoadTexture(const char* filename,			//where to load the file from
						 const unsigned int texID,		//arbitrary id you will reference the texture by does not have to be generated with glGenTextures
						 GLenum image_format = GL_RGB,	//format the image is in
						 GLint internal_format = GL_RGB,//format to store the image in
						 GLint level = 0,				//mipmapping level
						 GLint border = 0);				//border size

		//free the memory for a texture
		bool UnloadTexture(const unsigned int texID);

		//set the current texture
		bool BindTexture(const unsigned int texID);

		//free all texture memory
		void UnloadAllTextures();

	protected:
		TextureManager();
		TextureManager(const TextureManager& tm);
		TextureManager& operator=(const TextureManager& tm);
			
		static TextureManager* _inst;
		std::vector<GLuint> _texID;
		void loadTexture(const char* dirName, int textID);
		void loadTextureCube(const char* dirNameNX, const char* dirNameNY, 
							 const char* dirNameNZ, const char* dirNamePX, 
							 const char* dirNamePY, const char* dirNamePZ, 
							 int textID);
};