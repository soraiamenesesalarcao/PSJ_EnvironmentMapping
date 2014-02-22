#pragma once

#include "Utils.h"
#include <iostream>

class Entity {

	protected:
		std::string _id;
		int _solid;
		Entity(std::string id);

	public:
		virtual ~Entity();
		virtual void update() = 0;
		virtual void draw();
		std::string getId();
		int getSolid();
		void setSolid(int solid);
};