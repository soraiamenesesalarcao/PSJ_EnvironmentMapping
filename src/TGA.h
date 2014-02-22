#define TGA_RGB		2
#define TGA_A		3
#define TGA_RLE		10

typedef GLushort WORD;
typedef GLubyte byte;

typedef struct tImageTGA
{
	int channels;
	int size_x;	
	int size_y;				
	unsigned char *data;
} tImageTGA;


tImageTGA *Load_TGA(char *filename);
//void TGA_Texture(unsigned int textureArray[], char *strFileName, int textureID);



// www.morrowland.com
// apron@morrowland.com