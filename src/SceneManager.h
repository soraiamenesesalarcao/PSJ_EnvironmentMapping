#pragma once

#include "Definitions.h"
#include "Input.h"
#include "Entity.h"
#include "LightSource.h"
#include "Camera.h"
#include "TextureManager.h"
#include "Skybox.h"


class SceneManager {

	private:
		LightSource * _lightSource;
		glm::vec3 _ambientGlobal;
		SceneManager();
		GLuint _shaderProgram;

		GLuint* _vaoId;
		GLuint* _vboId;
		GLuint* _vaoIdEnv;
		GLuint* _vboIdEnv;

		std::vector<Entity*> _objectList;
		Skybox * _skybox;
		int _currentObject;
		int _mappingMode;
	
		/* The Uniform ID value */
		GLint _uniformBlockId;
		GLuint UBO_BP;

		void createEntities();
		void createSkyBox();
		void updateMapping();
		void changeShader();		
		void addEntity(Entity* entity);
		
	public:
		static SceneManager * getInstance();
		void init();
		void draw();
		void update();
		void createBufferObjects();
		void destroyBufferObjects();		
};