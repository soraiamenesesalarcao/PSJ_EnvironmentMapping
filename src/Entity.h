#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"


class Entity {
		

	private:
		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

		float _color[4];

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

		std::string _objFileDir;

		Entity(int solid, std::string name);
		void update();
		void draw(GLuint* vaoId);
		void setObjEntity(std::string fileName);
		void setMaterial(char* file); 
		void setTexture(const int id);
		void setColor(const float color[4]);
		void setColor(const float r, const float g, const float b, const float a);
		void rotate(float angle);
				
		void createBufferObjects(GLuint* vaoId, GLuint* vboId);
				
		std::string getName() const;
		std::string getObjFileDir();		

		void calculateModelMatrix();
		void calculateNormalMatrix();	

};