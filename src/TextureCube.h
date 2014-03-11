#pragma once

#include "Definitions.h"
#include "Texture.h"

class TextureCube : public Texture {

	private:
		GLuint _texID;
		std::string _files[6];

	public:
		TextureCube(std::string f1, std::string f2, std::string f3,
					std::string f4, std::string f5, std::string f6, 
					GLenum texUnit);
		void bind();
		void unbind();
		void draw();
};