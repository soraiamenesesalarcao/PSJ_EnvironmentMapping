#pragma once

#include "Definitions.h"
#include "Texture.h"

class Texture2D : public Texture {

	private:
		GLuint _texID;
		std::string _file;

	public:
		Texture2D(std::string file, int texUnit);
		~Texture2D();
		void bind();
		void unbind();
		void draw();
};