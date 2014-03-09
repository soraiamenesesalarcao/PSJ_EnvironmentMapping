#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "Texture2D.h"


class Entity {
		
	protected:
		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

		std::string _name;
		GLuint* _vaoId;
		GLuint* _vboId;

		Texture2D * _texture2D;

		//int _textureID;
		std::vector<Properties> _propertiesArray;
		std::vector<Vertex> _vertexArray;
		int _currentPropertyIndex;
		std::vector<glm::vec3> _modifiedVertexArray;
		glm::mat4 _currentModelMatrix;
		glm::mat3 _currentNormalMatrix;
		glm::quat _q;

		static const glm::vec3 DEFAULT_POSITION;
		static const glm::quat DEFAULT_ROTATION;
		static const glm::vec3 DEFAULT_SCALE;

	public:
		Entity(std::string name);
		Entity();

		std::string getName() const;

		void setMesh(char* file);
		void setMaterial(char* file); 
		//void setTexture(const int id);
		void setTexture2D(std::string file);

		void rotate(glm::vec3 axis);
		void draw();

		void createBufferObjects(GLuint* vaoId, GLuint* vboId);
		void calculateModelMatrix();
		void calculateNormalMatrix();	
};