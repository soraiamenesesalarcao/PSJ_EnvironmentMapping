#pragma once

#include "Definitions.h"
#include "Entity.h"
#include "Input.h"
#include "Camera.h"


class SceneManager {

	private:
		/* typedef std::map<const std::string, Entity *>::iterator entityIterator; 
		std::map<const std::string, Entity *> _entities; */
		Entity * _entity;
		SceneManager();
		GLuint _program;


	public:
		static SceneManager * getInstance();
		void init();
		//void add(Entity * entity);
		//Entity * getEntityById(std::string id);
		Entity * getEntity();
		void destroyBufferObjects();
		void draw();
		void update();
};