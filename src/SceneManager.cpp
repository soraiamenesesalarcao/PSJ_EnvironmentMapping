#include "SceneManager.h"


SceneManager::SceneManager(){

}


SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}


void SceneManager::init(){

	// Shader
	_program = ShaderProgram::getInstance()->createShaderProgram("shaders/vertex.glsl", "shaders/fragment.glsl");

	// Solid
	_entity = new Entity(CUBE);
	_entity->setMaterial("config/materials.xml", "ruby");
	// transformacoes e tal

	// LightSource
	_lightSource = new LightSource();
	_lightSource->setComponents("config/lights.xml", "main");
	
}


void SceneManager::draw(){

	ShaderProgram::getInstance()->bind(_program);

	// Camera
	Camera::getInstance()->put(); 
	
	// Solid
	// _entity->draw();

	// LightSource
	// _lightSource->draw();

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

	// Light distance
	
	if(Input::getInstance()->keyWasPressed('a')) {
		// _lightSource->moveLeft();
	}
	if(Input::getInstance()->keyWasPressed('d')) {
		// _lightSource->moveRight();
	}
	if(Input::getInstance()->keyWasPressed('w')) {
		// _lightSource->moveAhead();
	}
	if(Input::getInstance()->keyWasPressed('s')) {
		// _lightSource->moveBackwards();
	}
	if(Input::getInstance()->keyWasPressed('q')) {
		// _lightSource->moveUp();
	}
	if(Input::getInstance()->keyWasPressed('e')) {
		// _lightSource->moveDown();
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