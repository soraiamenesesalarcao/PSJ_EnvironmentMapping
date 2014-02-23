#pragma once

#include "Definitions.h"
#include "Entity.h"
#include "Input.h"
#include "Camera.h"


class SceneManager {

	private:
		Entity * _entity;
		SceneManager();
		GLuint _program;


	public:
		static SceneManager * getInstance();
		void init();
		Entity * getEntity();
		void destroyBufferObjects();
		void draw();
		void update();
};