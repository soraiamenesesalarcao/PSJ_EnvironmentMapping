#include "ConfigLoader.h"

namespace ConfigLoader {

	void loadMaterial(char* file, glm::vec3 &ambient, glm::vec3 &diffuse, glm::vec3 &specular, float &shininess){
		std::ifstream in(file, std::ios::in);
		if(!in){ 
			std::cerr << "Cannot open " << file << std::endl; 
			exit(1); 
		}

		std::string line;
		while (getline(in, line)) {
			if (line.substr(0,3) == "Ka "){
				std::istringstream s(line.substr(3));
				s >> ambient.x >> ambient.y >> ambient.z;
			}
			else if (line.substr(0,3) == "Kd "){
				std::istringstream s(line.substr(3));
				s >> diffuse.x >> diffuse.y >> diffuse.z;
			}
			else if (line.substr(0,3) == "Ks "){
				std::istringstream s(line.substr(3));
				s >> specular.x >> specular.y >> specular.z;
			}
			else if (line.substr(0,3) == "Ns "){
				std::istringstream s(line.substr(3));
				s >> shininess;
			}

		}
	}

	void loadLight(char* file, std::string lightID, glm::vec3 *viewpoint, glm::vec3 *ambient, glm::vec3 *diffuse, glm::vec3 *specular, glm::vec3 *attenuation) {
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

				temp = child->first_node("attenuation");
				for(attr = temp->first_attribute(), i = 0; attr != NULL; attr = attr->next_attribute(), i++)	{
					(*attenuation)[i] = atof(attr->value());
				}
			}
		}
	}
}