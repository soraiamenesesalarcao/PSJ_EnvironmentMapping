#pragma once

#include "Definitions.h"
#include "Input.h"
#include "Entity.h"
#include "LightSource.h"
#include "Camera.h"


class SceneManager {

	private:
		Entity * _entity;
		LightSource * _lightSource;
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