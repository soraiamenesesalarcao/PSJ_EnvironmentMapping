#pragma once

#include "Definitions.h"
#include "Texture.h"

class Texture2D : public Texture {

	private:
		std::string _file;

	public:
		Texture2D(std::string file, int texUnit);
		void bind();
		void unbind();
		void draw();
};