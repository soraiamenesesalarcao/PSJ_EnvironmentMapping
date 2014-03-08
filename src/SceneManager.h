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
		/*A list where all figures are stored*/
		std::vector<Entity*> _objectList;
		Skybox * _skybox;
		int _currentObject;
	
		/* The Uniform ID value */
		GLint _uniformBlockId;
		GLuint UBO_BP;
		
	public:
		static SceneManager * getInstance();
		void init();
		void draw();
		void update();
		void createBufferObjects();
		void destroyBufferObjects();
		void initObjects();
		void addEntity(Entity* entity);
};