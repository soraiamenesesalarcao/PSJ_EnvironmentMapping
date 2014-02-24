#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"

class LightSource {

	private:
		glm::vec3 _position;
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;

	public:
		LightSource();		
		void setComponents(char* file, std::string lightID);
		void moveLeft();
		void moveRight();
		void moveAhead();
		void moveBackwards();
		void moveUp();
		void moveDown();
		void draw();
};