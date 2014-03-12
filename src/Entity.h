#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"
#include "TextureManager.h"
#include "Input.h"
#include "Camera.h"
#include "Texture2D.h"
#include "TextureCube.h"
#include "TextureBumpMapping.h"


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
		TextureCube * _textureCube;
		TextureBumpMapping * _textureBumpMapping;

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
		void setTexture2D(std::string file, int texUnit);
		void setTextureCube(std::string f1, std::string f2, std::string f3,
							std::string f4, std::string f5, std::string f6, 
							int texUnit);
		void setTextureBumpMapping(std::string file_texture, int texUnit,
									std::string file_normal, int texUnit2);
		void cleanTextures();
		void rotate(glm::vec3 axis);
		void draw(int mode);

		void createBufferObjects(GLuint* vaoId, GLuint* vboId);
		void calculateModelMatrix();
		void calculateNormalMatrix();	
};