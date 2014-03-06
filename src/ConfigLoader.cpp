#include "ConfigLoader.h"

namespace ConfigLoader {

	void loadMesh(const char* fileName, std::vector<Vertex> * vertexArray){
        std::string line = std::string();
        std::ifstream file(fileName);

		//Temporary arrays to store loaded information
        std::vector<glm::vec4> vertices, normals;
		std::vector<glm::vec2> uvs;
        
        if (file.is_open()) {
                while (getline(file, line)) {
					std::vector<std::string> splitedLine = Utils::explode(line, ' ');
					if(splitedLine.size() > 0){
						if(splitedLine[0] == "#"){
							continue; //Comment in obj, skip this line
						}
						else if(splitedLine[0] == "v"){ //Ex line => v 1.00000 0.45555 1.10000
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							vertices.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "vt"){ //Ex line => vt 1.00000 0.45555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							uvs.push_back(glm::vec2(x,y));
						}
						else if(splitedLine[0] == "vn"){ //Ex line => vn 1.00000 0.45555 0.65555
							float x = atof(splitedLine[1].c_str());
							float y = atof(splitedLine[2].c_str());
							float z = atof(splitedLine[3].c_str());
							normals.push_back(glm::vec4(x,y,z,1.0f));
						}
						else if(splitedLine[0] == "f"){ 
							Vertex vertex1, vertex2, vertex3;
							std::vector<std::string> face1 = Utils::explode(splitedLine[1], '/');
							std::vector<std::string> face2 = Utils::explode(splitedLine[2], '/');
							std::vector<std::string> face3 = Utils::explode(splitedLine[3], '/');
							//Copy vertex information from temporary vertices array to vertices
							memcpy(vertex1.XYZW, &vertices[atoi(face1[0].c_str())-1][0], sizeof(vertex1.XYZW));
							memcpy(vertex2.XYZW, &vertices[atoi(face2[0].c_str())-1][0], sizeof(vertex2.XYZW));
							memcpy(vertex3.XYZW, &vertices[atoi(face3[0].c_str())-1][0], sizeof(vertex3.XYZW));
							if((face1.size() > 1) && face1[1].size() > 0){
								//UV information
								memcpy(vertex1.UV, &uvs[atoi(face1[1].c_str())-1][0], sizeof(vertex1.UV));
								memcpy(vertex2.UV, &uvs[atoi(face2[1].c_str())-1][0], sizeof(vertex2.UV));
								memcpy(vertex3.UV, &uvs[atoi(face3[1].c_str())-1][0], sizeof(vertex3.UV));
							}
							if((face1.size() > 2) && face1[2].size() > 0){
								//Normal information
								memcpy(vertex1.NORMAL, &normals[atoi(face1[2].c_str())-1][0], sizeof(vertex1.NORMAL));
								memcpy(vertex2.NORMAL, &normals[atoi(face2[2].c_str())-1][0], sizeof(vertex2.NORMAL));
								memcpy(vertex3.NORMAL, &normals[atoi(face3[2].c_str())-1][0], sizeof(vertex3.NORMAL));
							}
							vertexArray->push_back(vertex1);
							vertexArray->push_back(vertex2);
							vertexArray->push_back(vertex3);
						}
					}
                }
        }
        else{
			std::cerr << "Cannot open " << fileName << std::endl; exit(1);
		}
	}

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