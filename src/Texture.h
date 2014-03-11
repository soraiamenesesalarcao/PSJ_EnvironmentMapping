#pragma once

#include "Definitions.h"
#include "ShaderProgram.h"

class Texture {

	protected:
		GLenum _texUnitEnum;
		int _texUnitInt;
		std::vector<GLuint> _MtexID; // vania ve isto LOLs
	//	GLuint _texID[2];
		Texture(int texUnit);
	//	~Texture();
	public:		
		virtual void bind() = 0;
		virtual void unbind() = 0;
		virtual void draw() = 0;
};