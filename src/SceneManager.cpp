#include "SceneManager.h"


SceneManager::SceneManager(){}

SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}

void SceneManager::init(){

	// Shader
	_shaderProgram = ShaderProgram::getInstance()->createShaderProgram( "shaders/vertexShaderUniforms.glsl", 
																		"shaders/fragmentShaderUniforms.glsl");
	TextureManager::Inst();
	_currentObject = TEAPOT;
	initObjects();
	createBufferObjects();

	// LightSource
	_lightSource = new LightSource();
	_lightSource->setComponents("config/lights.xml", "main");
	_ambientGlobal = glm::vec3(0.2, 0.2, 0.2);
}

void SceneManager::draw(){
	if(!_objectList.empty()){
		ShaderProgram::getInstance()->bind(_shaderProgram);

		// Camera
		Camera::getInstance()->put(); 

		// Draw solid
		_objectList[_currentObject]->draw();

		// LightSource
		GLint ambientGId = ShaderProgram::getInstance()->getId("LightAmbientGlobal");
		glUniform3fv(ambientGId, 1, glm::value_ptr(_ambientGlobal));
		 _lightSource->draw();

		ShaderProgram::getInstance()->unBind();
	}
}

void SceneManager::update(){

	// Solid type
	if(Input::getInstance()->keyWasReleased('T')) {
		_currentObject = (_currentObject + 1) % NSOLIDS;
		_objectList[_currentObject]->createBufferObjects(_vaoId, _vboId);
	}

	if(Input::getInstance()->keyWasReleased('m')){
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
	if(Input::getInstance()->keyWasPressed('a')) {
		 _lightSource->decX();
	}
	if(Input::getInstance()->keyWasPressed('d')) {
		 _lightSource->incX();
	}
	if(Input::getInstance()->keyWasPressed('s')) {
		 _lightSource->decY();
	}
	if(Input::getInstance()->keyWasPressed('w')) {
		 _lightSource->incY();
	}	
	if(Input::getInstance()->keyWasPressed('q')) {
		 _lightSource->decZ();
	}
	if(Input::getInstance()->keyWasPressed('e')) {
		 _lightSource->incZ();
	}

	// Rotation
	if(Input::getInstance()->mouseWasPressed(GLUT_LEFT_BUTTON)){ // x
		_objectList[_currentObject]->rotate(glm::vec3(1.0, 0.0, 0.0));
	}
	if(Input::getInstance()->mouseWasPressed(GLUT_RIGHT_BUTTON)){ // y
		_objectList[_currentObject]->rotate(glm::vec3(0.0, 1.0, 0.0));
	}
	if(Input::getInstance()->mouseWasPressed(GLUT_MIDDLE_BUTTON)){ // z
		_objectList[_currentObject]->rotate(glm::vec3(0.0, 0.0, 1.0));
	}

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

void SceneManager::createBufferObjects(){
	_vaoId = new GLuint[1];
	_vboId = new GLuint[2];

	glGenVertexArrays(1, _vaoId);	//Vertex Array
	glGenBuffers(2, _vboId);		//Buffer Array

	//create buffer for specific entity
	_objectList[_currentObject]->createBufferObjects(_vaoId, _vboId);
	
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

void SceneManager::initObjects(){
	Entity* teapot = new Entity("Teapot");
	teapot->setMesh("objects/teapot.obj");
	teapot->setMaterial("materials/ruby.mtl");
	//teapot->setTexture(TextureManager::STONE);
	addEntity(teapot);

	Entity* cube = new Entity("Cube");
	cube->setMesh("objects/cube.obj");
	cube->setMaterial("materials/ruby.mtl");
	//cube->setTexture(TextureManager::FIRE);
	addEntity(cube);
}

void SceneManager::addEntity(Entity* entity){
	_objectList.push_back(entity);
}

