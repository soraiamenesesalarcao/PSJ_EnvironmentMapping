#pragma once

#include "Definitions.h"
#include "Input.h"
#include "Entity.h"
//#include "LightSource.h"
#include "Camera.h"

#include <vector>

class SceneManager {



	private:
		Entity * _entity;
		//LightSource * _lightSource;
		SceneManager();
		GLuint _shaderProgram;

		GLuint* _vaoId;
		GLuint* _vboId;
		/*A list where all figures are stored*/
		std::vector<Entity*> _objectList;
	
		/* The Uniform ID value */
		GLint _uniformBlockId;
		GLuint UBO_BP;

	public:
		static SceneManager * getInstance();
		void init();
		Entity * getEntity();
		void destroyBufferObjects();

		//draw the specific object
		void draw();
		void update();

		void initObjects();
		void createBufferObjects();
		void addEntity(Entity* entity);

};