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
#define NORMALS 1
#define UVS 2
#define COLORS 3
#define NSOLIDS 2
#define TEAPOT 0
#define CUBE 1
#define LIGHT_OFFSET 1

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;
