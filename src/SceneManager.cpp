#include "SceneManager.h"
#include "TextureManager.h"


SceneManager::SceneManager(){}

SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}

void SceneManager::addEntity(Entity* entity){
	_objectList.push_back(entity);
}


void SceneManager::init(){

	// Shader
	_shaderProgram = ShaderProgram::getInstance()->createShaderProgram("shaders/vertexShader.glsl", "shaders/fragmentShader.glsl");
	TextureManager::Inst();
	f_Cube = true;
	_currentObject = TEAPOT;
	initObjects();
	createBufferObjects();

	// LightSource
	//_lightSource = new LightSource();
	//_lightSource->setComponents("config/lights.xml", "main");
}

void SceneManager::initObjects(){
	Entity* teapot = new Entity(TEAPOT, "Teapot");
	teapot->setObjEntity("../scripts/objects/teapot.obj");
	//teapot->setTexture(TextureManager::STONE);
	addEntity(teapot);

	Entity* cube = new Entity(CUBE, "Cube");
	cube->setObjEntity("../scripts/objects/cube.obj");
	//cube->setTexture(TextureManager::FIRE);
	addEntity(cube);
}

void SceneManager::createBufferObjects(){
	_vaoId = new GLuint[1];
	_vboId = new GLuint[2];

	glGenVertexArrays(1, _vaoId);	//Vertex Array
	glGenBuffers(2, _vboId);		//Buffer Array

	//create buffer for specific entity
	if(f_Cube){
		_objectList[TEAPOT]->createBufferObjects(_vaoId, _vboId);
	}else{
		_objectList[CUBE]->createBufferObjects(_vaoId, _vboId);
	}
	
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
	if(!_objectList.empty()){
		ShaderProgram::getInstance()->bind(_shaderProgram);

		// Camera
		Camera::getInstance()->put(); 

		// draw solids
		if(f_Cube){
			_objectList[TEAPOT]->draw(_vaoId, ShaderProgram::getInstance()->getModelMatrixUniformId(),
				ShaderProgram::getInstance()->getColorUniformId(),
				ShaderProgram::getInstance()->getTextureUniformId());

		}else{
			_objectList[CUBE]->draw(_vaoId, ShaderProgram::getInstance()->getModelMatrixUniformId(),
				ShaderProgram::getInstance()->getColorUniformId(),
				ShaderProgram::getInstance()->getTextureUniformId());
		}

		// LightSource
		// _lightSource->draw();

		ShaderProgram::getInstance()->unBind();
	}
}

void SceneManager::update(){

	// Solid type
	if(Input::getInstance()->keyWasReleased('T')) {
		if(f_Cube) {
			f_Cube = false;
			_objectList[CUBE]->createBufferObjects(_vaoId, _vboId);
			_currentObject = CUBE;
		}
		else {
			f_Cube = true;
			_objectList[TEAPOT]->createBufferObjects(_vaoId, _vboId);
			_currentObject = TEAPOT;
		}
	}

	if(Input::getInstance()->keyWasReleased('Q')){
		exit(0);
	}

	// Material
	
	if(Input::getInstance()->keyWasReleased('1')) {
		_objectList[_currentObject]->setMaterial("materials/ruby.mtl");
	}
	if(Input::getInstance()->keyWasReleased('2')) {
		_objectList[_currentObject]->setMaterial("materials/gold.mtl");
	}
	if(Input::getInstance()->keyWasReleased('3')) {
		_objectList[_currentObject]->setMaterial("materials/silver.mtl");
	}
	if(Input::getInstance()->keyWasReleased('4')) {
		_objectList[_currentObject]->setMaterial("materials/esmerald.mtl");
	}
	if(Input::getInstance()->keyWasReleased('5')) {
		_objectList[_currentObject]->setMaterial("materials/cyan.mtl");
	}

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

	if(f_Cube){ _objectList[TEAPOT]->update(); }
	else{ _objectList[CUBE]->update(); }

	// Camera 
	Camera::getInstance()->update();
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

	glDeleteBuffers(3, _vboId);
	glDeleteVertexArrays(1, _vboId);

	Camera::getInstance()->~Camera();
}
