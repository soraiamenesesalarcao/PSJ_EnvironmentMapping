#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"

class Entity {

	private:
		int _solid;
		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

	public:
		Entity(int solid);
		Entity();
		void update();
		void draw();
		int getSolid();
		void changeSolid();
		void setMaterial(char* file, std::string matID);
};