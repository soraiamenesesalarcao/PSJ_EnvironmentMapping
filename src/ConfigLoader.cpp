#include "ConfigLoader.h"

namespace ConfigLoader {

	void loadMaterial(char* file, std::string matID, glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular, float *shininess) {
		int i;

		rapidxml::xml_document<> doc;
		doc.parse<0>(Utils::readFile(file));

		rapidxml::xml_node<> * rootNode = doc.first_node("materials");
		rapidxml::xml_node<> * temp;

		for(rapidxml::xml_node<> *child = rootNode->first_node("material"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(matID) == 0) {
	
				i = 0;
				temp = child->first_node("ambient");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++) {
					(*ambient)[i] = atof(attr->value());
				}

				i = 0;
				temp = child->first_node("diffuse");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++)	{
					(*diffuse)[i] = atof(attr->value());
				}

				i = 0;
				temp = child->first_node("specular");
				for(rapidxml::xml_attribute<> *attr = temp->first_attribute(); attr != NULL; attr = attr->next_attribute(), i++)	{
					(*specular)[i] = atof(attr->value());
				}
				
				temp = child->first_node("shininess");
				*shininess = atof(temp->value());
			}
		}
	}
}