#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <gtc/quaternion.hpp>

namespace Utils {
	
	bool isOpenGLError();
	void checkOpenGLError(std::string error);	
	char * readFile(char * file);
}
