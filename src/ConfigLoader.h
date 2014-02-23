#include <iostream>

#include <rapidxml.hpp>
#include <rapidxml_print.hpp>

#include <glm.hpp>
#include <gtc/quaternion.hpp>

#include "Utils.h"

namespace ConfigLoader {

	void loadMaterial(char* file, std::string matID, glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular, float *shininess);
}
