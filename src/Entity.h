#pragma once

#include "Definitions.h"
#include "Utils.h"

class Entity {

	protected:
	//	std::string _id;
		int _solid;
		std::string _matID;

	public:
		Entity(std::string matID);
		Entity();
		void update();
		void draw();
		//std::string getId();
		int getSolid();
		void changeSolid();
		std::string getMaterial();
		void setMaterial(std::string matID);
};