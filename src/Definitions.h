#include "GL/glew.h"
#include "GL/freeglut.h"

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define UVS 3

#define MAX(a,b) (((a)>(b))?(a):(b))
#define MIN(a,b) (((a)<(b))?(a):(b))
#define SWAP(T, a, b) {T temp = a; a = b; b = temp;}

typedef struct {
	GLfloat XYZW[4];
	GLfloat RGBA[4];
} Vertex;
