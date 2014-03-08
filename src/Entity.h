#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"


class Entity {
		
	protected:
		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

		std::string _name;
		GLuint* _vaoId;
		GLuint* _vboId;

		int _textureID;
		std::vector<Properties> _propertiesArray;
		std::vector<Vertex> _vertexArray;
		int _currentPropertyIndex;
		//std::vector<Program*> _programsToUse;
		std::vector<glm::vec3> _modifiedVertexArray;
		glm::mat4 _currentModelMatrix;
		glm::mat4 _currentNormalMatrix;
		glm::quat _q;

		static const glm::vec3 DEFAULT_POSITION;
		static const glm::quat DEFAULT_ROTATION;
		static const glm::vec3 DEFAULT_SCALE;

	public:
		Entity(std::string name);
		Entity();
		void draw();
		void setMesh(char* file);
		void setMaterial(char* file); 
		void setTexture(const int id);
		void rotate(glm::vec3 axis);			
				
		std::string getName() const;
		//std::string getObjFileDir();

		void createBufferObjects(GLuint* vaoId, GLuint* vboId);
		void calculateModelMatrix();
		void calculateNormalMatrix();	
};