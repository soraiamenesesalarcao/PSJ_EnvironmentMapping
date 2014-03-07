#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/intersect.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/transform.hpp>
#include <gtx/transform2.hpp>
#include <gtc/matrix_transform.hpp>
#include <ext.hpp>

#include "SOIL.h"

#include <iostream>
#include <vector>


#define VERTICES 0
#define NORMALS 1
#define UVS 2
#define NSOLIDS 5
//#define TEAPOT 0
#define CYLINDER 0
#define CUBE 1
#define TORUS 2
#define SPHERE 3
#define QUAD 4

#define LIGHT_OFFSET 1
#define ANGLE_OFFSET 0.05
#define ROTATION_DELAY 1.0f
#define TEX_FIRE 0
#define TEX_STONE 1
#define TEX_ENV_CUBE 2

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	float XYZW[4];
	float NORMAL[4];
	float UV[2];
} Vertex;

typedef struct {
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
} Properties;