#pragma once

#include "Definitions.h"
#include "Utils.h"

#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

namespace ConfigLoader {

	void loadMaterial(char* file, std::string matID, 
					  glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular, float *shininess);
}
