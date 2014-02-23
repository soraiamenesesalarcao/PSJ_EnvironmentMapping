#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/transform2.hpp>
#include <ext.hpp>

#include <iostream>
//#include <map>

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define UVS 3
#define NSOLIDS 2
#define CUBE 0
#define TEAPOT 1
#define LIGHT_OFFSET_X 1

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;
