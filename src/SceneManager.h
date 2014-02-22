#pragma once

#include "Entity.h"
#include "Input.h"

/*#include "Camera.h"
#include "TangramPieces.h"
#include "Board.h"
#include "Mirror.h"
#include "Quad.h"
#include "Light.h"*/

#include <iostream>
#include <map>



class SceneManager {

	private:
		typedef std::map<const std::string, Entity *>::iterator entityIterator;
		std::map<const std::string, Entity *> _entities;
		SceneManager();
		/*Light * _light;
		Quad * _quad;
		Mirror * _mirror;
		Entity * _selected;
		GLuint frameBufferPP;
		GLuint texColorBufferNoise;
		GLuint _postProgram;*/
		GLuint _program;

		//bool _greyscale, _noise, _vignette, _freichen;
		//float animationTryOut;


	public:
		static SceneManager * getInstance();
		void init();
		void add(Entity * entity);
		Entity * getEntityById(std::string id);
		//bool isMouseOver(std::string id);
		void destroyBufferObjects();
		void draw();
		void update();
		//void postProcessing();
};