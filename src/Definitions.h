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
#define TANGENTS 3

#define NSOLIDS 6
#define TEAPOT 0
#define CYLINDER 1
#define CUBE 2
#define TORUS 3
#define SPHERE 4
#define QUAD 5

#define LIGHT_OFF 0
#define LIGHT_ON 1
#define LIGHT_OFFSET 0.01
#define ANGLE_OFFSET 0.05
#define ROTATION_DELAY 1.0f

#define TEX_ENV_CUBE 0
#define TEX_STONE 1
#define TEX_FIRE 2

#define TEX_UNIT_0 0
#define TEX_UNIT_1 1
#define TEX_UNIT_2 2

#define TEX_2D 0
#define TEX_CUBE 1
#define TEX_NORMAL 2

#define NMAPINGS 3
#define CUBE_MAPPING 0
#define SPHERE_MAPPING 1
#define BUMP_MAPPING 2

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	float XYZW[4];
	float NORMAL[4];
	float UV[2];
	float TANGENT[4];
} Vertex;

typedef struct {
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
} Properties;