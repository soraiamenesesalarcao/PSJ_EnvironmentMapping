#pragma once

#include "Definitions.h"
#include "Texture.h"

class TextureBumpMapping : public Texture {

	private:
		std::vector<GLuint> _texID;
		std::string _file_textura;
		std::string _file_normal;

	public:
		TextureBumpMapping(std::string file_textura,int texUnit, std::string file_normal, int texUnit2);
		~TextureBumpMapping();
		void bind();
		void unbind();
		void draw();
};