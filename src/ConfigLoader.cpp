#include "ConfigLoader.h"

namespace ConfigLoader {

	void loadMaterial(char* file, std::string matID, glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular, float *shininess) {
		int i;

		rapidxml::xml_document<> doc;
		doc.parse<0>(Utils::readFile(file));

		rapidxml::xml_node<> * rootNode = doc.first_node("materials");
		rapidxml::xml_node<> * temp;
		rapidxml::xml_attribute<> *attr;

		for(rapidxml::xml_node<> *child = rootNode->first_node("material"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(matID) == 0) {
					
				temp = child->first_node("ambient");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++) {
					(*ambient)[i] = atof(attr->value());
				}
				
				temp = child->first_node("diffuse");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++)	{
					(*diffuse)[i] = atof(attr->value());
				}
				
				temp = child->first_node("specular");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++)	{
					(*specular)[i] = atof(attr->value());
				}				
				temp = child->first_node("shininess");
				*shininess = atof(temp->value());
			}
		}
	}

	void loadLight(char* file, std::string lightID, glm::vec3 *viewpoint, glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular) {
		int i;

		rapidxml::xml_document<> doc;
		doc.parse<0>(Utils::readFile(file));

		rapidxml::xml_node<> * rootNode = doc.first_node("lights");
		rapidxml::xml_node<> * temp;
		rapidxml::xml_attribute<> *attr;

		for(rapidxml::xml_node<> *child = rootNode->first_node("light"); child != NULL; child = child->next_sibling()) {
			if(std::string(child->first_attribute("id")->value()).compare(lightID) == 0) {
				
				temp = child->first_node("viewpoint");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++) {
					(*viewpoint)[i] = atof(attr->value());
				}

				temp = child->first_node("ambient");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++) {
					(*ambient)[i] = atof(attr->value());
				}
				
				temp = child->first_node("diffuse");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++)	{
					(*diffuse)[i] = atof(attr->value());
				}
				
				temp = child->first_node("specular");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++)	{
					(*specular)[i] = atof(attr->value());
				}				
			}
		}
	}
}