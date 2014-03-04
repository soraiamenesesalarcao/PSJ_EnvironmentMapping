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
		glm::vec3 _attenuation;


	public:
		LightSource();		
		void setComponents(char* file, std::string lightID);
		void incX();
		void decX();
		void incY();
		void decY();
		void incZ();
		void decZ();
		void draw();
};