#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"
#include "TextureManager.h"
#include "Input.h"
#include <iostream>
#include <Vector>
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <glm.hpp>
#include <gtx\intersect.hpp>
#include <gtc\quaternion.hpp>
#include <gtx\quaternion.hpp>

class Entity {

	static const glm::vec3 DEFAULT_POSITION;
	static const glm::quat DEFAULT_ROTATION;
	static const glm::vec3 DEFAULT_SCALE;

	public:
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

	std::string _objFileDir;

	private:
		int _solid;
		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

		float _color[4];

		std::string _name;
		GLuint _vaoId;
		GLuint _vboId;

		int _textureID;
		std::vector<Properties> _propertiesArray;
		std::vector<Vertex> _vertexArray;
		int _currentPropertyIndex;
		//std::vector<Program*> _programsToUse;
		std::vector<glm::vec3> _modifiedVertexArray;
		glm::mat4 _currentModelMatrix;

		glm::quat _q;

	public:

		Entity(int solid, std::string name);
		void update();
		void draw(GLuint* vaoId, GLuint programId, GLuint programColorId, GLuint programTextureId);
		int getSolid();
		void changeSolid();
		void setMaterial(char* file); 
		
		void setObjEntity(std::string fileName);
		void createBufferObjects(GLuint* vaoId, GLuint* vboId);

		std::vector<std::string> explode(const std::string &s, char delim);
		void loadMesh(const char* fileName);

		std::string getName() const;

		std::string getObjFileDir();

		//Setters
		void setVaoId(int value);
		void setVboId(int value);
		void setTexture(const int id);

		void calculateModelMatrix();

		void setColor(const float color[4]);
		void setColor(const float r, const float g, const float b, const float a);
		void rotate(float angle);

};