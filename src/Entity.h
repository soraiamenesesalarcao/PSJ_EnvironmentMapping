#pragma once

#include "Definitions.h"
#include "Utils.h"
#include "ConfigLoader.h"

class Entity {

	private:
	//	std::string _id;
		int _solid;
	//	std::string _matID;

		glm::vec3 _ambientMaterial;
		glm::vec3 _diffuseMaterial;
		glm::vec3 _specularMaterial;
		float _shininess;

	public:
		Entity(int solid);
		Entity();
		void init();
		void update();
		void draw();
		//std::string getId();
		int getSolid();
		void changeSolid();
		//std::string getMaterial();
		void setMaterial(char* file, std::string matID);
};