#pragma once

#include "Entity.h"

class Skybox : public Entity {

	public:
		Skybox();
		~Skybox();
		void draw(int mode);
};