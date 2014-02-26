#include "SceneManager.h"
#include "TextureManager.h"


SceneManager::SceneManager(){}


SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}

void SceneManager::addEntity(Entity* entity){
	//entity->setVaoId(_vaoCounter++);
	//entity->setVboId(_vboCounter++);

	//Add the Entity to the object list
	_objectList.push_back(entity);
}


void SceneManager::init(){

	// Shader
	_shaderProgram = ShaderProgram::getInstance()->createShaderProgram("shaders/VertexShader3.glsl", "shaders/FragmentShader3.glsl");
	initObjects();
	createBufferObjects();
	TextureManager::Inst();

	// LightSource
	//_lightSource = new LightSource();
	//_lightSource->setComponents("config/lights.xml", "main");
	
}

void SceneManager::initObjects(){
	_entity = new Entity(CUBE, "Cube");
	_entity->setObjEntity("../src/cube.obj");
	_entity->setTexture(TextureManager::RED);
	addEntity(_entity);

	//_entity = new Entity(CUBE);
	//_entity->setObjEntity("../src/objs/cube.obj");
	//_entity->setTexture(TextureManager::GREEN); example
	//addEntity(_entity);
}

void SceneManager::createBufferObjects(){
	_vaoId = new GLuint[1];
	_vboId = new GLuint[2];

	glGenVertexArrays(1, _vaoId);	//Vertex Array
	glGenBuffers(2, _vboId);		//Buffer Array

	//create buffer for specific entity
	//if(CUBE){
	_entity->createBufferObjects(_vaoId, _vboId);
	//}	

	//Reserve space for the Uniform Blocks
	glBindBuffer(GL_UNIFORM_BUFFER, _vboId[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(float)*16*2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _vboId[1]);

	// Clear buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0); //Vertices
	glDisableVertexAttribArray(1); //Normals
	glDisableVertexAttribArray(2); //UVs
}

void SceneManager::draw(){
	//if(!_objectList.empty()){
		ShaderProgram::getInstance()->bind(_shaderProgram);

		// Camera
		Camera::getInstance()->put(); 

		//if(cube){
		//	_objectList[0]->draw(_vaoId);
		//}else{
			//_objectList[1]->draw(_vaoId);
		//}
		_entity->draw(_vaoId, ShaderProgram::getInstance()->getModelMatrixUniformId(),
			ShaderProgram::getInstance()->getColorUniformId(),
			ShaderProgram::getInstance()->getTextureUniformId());


		// LightSource
		// _lightSource->draw();

		ShaderProgram::getInstance()->unBind();
	//}
}

void SceneManager::update(){


	// Solid type
	if(Input::getInstance()->keyWasReleased('T')) {
		_entity->changeSolid();
	}

	// Material
	/*if(Input::getInstance()->keyWasReleased('1')) {
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
	}*/

	// Light distance
	
/*	if(Input::getInstance()->keyWasPressed('a')) {
		 _lightSource->moveLeft();
	}
	if(Input::getInstance()->keyWasPressed('d')) {
		 _lightSource->moveRight();
	}
	if(Input::getInstance()->keyWasPressed('w')) {
		 _lightSource->moveAhead();
	}
	if(Input::getInstance()->keyWasPressed('s')) {
		 _lightSource->moveBackwards();
	}
	if(Input::getInstance()->keyWasPressed('q')) {
		 _lightSource->moveUp();
	}
	if(Input::getInstance()->keyWasPressed('e')) {
		 _lightSource->moveDown();
	}*/


	// Camera 
	Camera::getInstance()->update();
	
	/*for (entityIterator i = _entities.begin(); i != _entities.end(); i++)
		i->second->update();*/
}

void SceneManager::destroyBufferObjects(){
	_objectList.clear();
	ShaderProgram::getInstance()->destroyShaderProgram();
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(4, _vboId);
	glDeleteVertexArrays(1, _vboId);

	Camera::getInstance()->~Camera();
}
