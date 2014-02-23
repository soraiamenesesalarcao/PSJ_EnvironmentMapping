#include "SceneManager.h"


SceneManager::SceneManager(){

}


SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}

/*
void SceneManager::add(Entity * entity){
	_entities.insert(std::make_pair(entity->getId(), entity));
}


Entity * SceneManager::getEntityById(std::string id){
	return _entities.find(id)->second;
}
*/

void SceneManager::init(){

	//glm::quat qcoords;
	//glm::vec3 pcoords;

	_program = ShaderProgram::getInstance()->createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");
	_entity = new Entity(CUBE);
	_entity->setMaterial("config/materials.xml", "ruby");
	// transformacoes e tal
	
	/* Exemplo * /
	Utils::loadScene("scene/currentScene.xml", "quadradoAmarelo", &qcoords, &pcoords);
	TangramPieces * quadradoAmarelo = new TangramPieces("quadradoAmarelo");
	quadradoAmarelo->setMesh("mesh/parallellogram.obj", "materials/quadradoAmarelo.mtl");
	quadradoAmarelo->setTexture("materials/quadradoAmarelo.mtl");
	quadradoAmarelo->scale(1, 1, 0.15);
	quadradoAmarelo->setPos(pcoords.x, pcoords.y, pcoords.z, qcoords);
	add(quadradoAmarelo);
	/**/
	
}


void SceneManager::draw(){

	ShaderProgram::getInstance()->bind(_program);
	Camera::getInstance()->put(); 
	

	ShaderProgram::getInstance()->unBind();
}

void SceneManager::update(){


	// Solid type
	if(Input::getInstance()->keyWasReleased('T')) {
		_entity->changeSolid();
	}

	// Material
	if(Input::getInstance()->keyWasReleased('1')) {
		_entity->setMaterial("config/materials.xml", "ruby");
	}
	if(Input::getInstance()->keyWasReleased('2')) {
		_entity->setMaterial("config/materials.xml", "gold");
	}
	if(Input::getInstance()->keyWasReleased('3')) {
		_entity->setMaterial("config/materials.xml", "silver");
	}
	if(Input::getInstance()->keyWasReleased('4')) {
		_entity->setMaterial("config/materials.xml", "esmerald");
	}
	if(Input::getInstance()->keyWasReleased('5')) {
		_entity->setMaterial("config/materials.xml", "cyan");
	}

	// Camera 
	Camera::getInstance()->update();
	
	/*for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->update();*/
}



void SceneManager::destroyBufferObjects(){
	ShaderProgram::getInstance()->destroyShaderProgram();
	//for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
	//	i->second->~Entity();
	Camera::getInstance()->~Camera();
}