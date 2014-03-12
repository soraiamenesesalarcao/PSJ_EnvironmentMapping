#include "SceneManager.h"


SceneManager::SceneManager(){}

SceneManager * SceneManager::getInstance(){
	static SceneManager instance;
	return &instance;
}


void SceneManager::createEntities(){
	
	Entity* teapot = new Entity("Teapot");
	Entity* cylinder = new Entity("Cylinder");
	Entity* torus = new Entity("Torus");
	Entity* cube = new Entity("Cube");
	Entity* sphere = new Entity("Sphere");
	Entity* quad = new Entity("Quad");

	// Meshes
	teapot->setMesh("objects/teapot.obj");
	cylinder->setMesh("objects/cylinder.obj");
	torus->setMesh("objects/torus.obj");
	cube->setMesh("objects/cube.obj");
	sphere->setMesh("objects/sphere.obj");
	quad->setMesh("objects/quad.obj");
	
	// Materials
	teapot->setMaterial("materials/silverBM.mtl");	
	cylinder->setMaterial("materials/silverBM.mtl");	
	torus->setMaterial("materials/silverBM.mtl");
	cube->setMaterial("materials/silverBM.mtl");
	sphere->setMaterial("materials/silverBM.mtl");
	quad->setMaterial("materials/silverBM.mtl");
	
	// Adding to entities list
	addEntity(teapot);
	addEntity(cylinder);
	addEntity(torus);
	addEntity(cube);
	addEntity(sphere);
	addEntity(quad);
	_skybox = NULL;

}

void SceneManager::createSkyBox() {
	_skybox = new Skybox();
	_skybox->setMesh("objects/sphere.obj");
	_skybox->setMaterial("materials/silver.mtl");		
}

void SceneManager::updateMapping() {
	

	switch(_mappingMode) {
		case CUBE_MAPPING:	
			std::cout << "cube mapping " << std::endl;
			for (int i = 0; i < NSOLIDS; i++){
				_objectList[i]->cleanTextures();
				_objectList[i]->setTextureCube("textures/posx.jpg", "textures/negx.jpg", "textures/posy.jpg",
									"textures/negy.jpg", "textures/posz.jpg", "textures/negz.jpg",
									TEX_UNIT_0);
			}
			createSkyBox();
			_skybox->setTextureCube("textures/posx.jpg", "textures/negx.jpg", "textures/posy.jpg",
								"textures/negy.jpg", "textures/posz.jpg", "textures/negz.jpg",
								TEX_UNIT_0);
			break;
		case SPHERE_MAPPING:
			std::cout << "sphere mapping " << std::endl;
			for (int i = 0; i < NSOLIDS; i++){				
				_objectList[i]->cleanTextures();
				_objectList[i]->setTexture2D("textures/spheremap.jpg", TEX_UNIT_0);
			}
			if(_skybox != NULL) {
				_skybox->~Skybox();
				_skybox = NULL;
			}
			break;
		case BUMP_MAPPING:
			std::cout << "bump mapping " << std::endl;
			for (int i = 0; i < NSOLIDS; i++){				
				_objectList[i]->cleanTextures();
				//_objectList[i]->setTexture2D("textures/spheremap.jpg", TEX_UNIT_0);
				_objectList[i]->setTextureBumpMapping("textures/rock.jpg", TEX_UNIT_1,
														"textures/normalMapRock.jpg", TEX_UNIT_0);
			}
			if(_skybox != NULL) {
					_skybox->~Skybox();
					_skybox = NULL;
			}
			break;
		default:
			;
	}

}

void SceneManager::changeShader() {
	switch(_mappingMode) {
		case CUBE_MAPPING:
			_shaderProgram = ShaderProgram::getInstance()->createShaderProgram("shaders/vertexShader_CubeMapping.glsl", 
																			"shaders/fragmentShader_CubeMapping.glsl");
			break;
		case SPHERE_MAPPING:
			_shaderProgram = ShaderProgram::getInstance()->createShaderProgram("shaders/vertexShader_SphereMapping.glsl", 
																			"shaders/fragmentShader_SphereMapping.glsl");
			break;
		case BUMP_MAPPING:
			_shaderProgram = ShaderProgram::getInstance()->createShaderProgram("shaders/vertexShader_BumpMapping.glsl", 
																			"shaders/fragmentShader_BumpMapping.glsl");
			break;
		default:
			;
	}
}

void SceneManager::addEntity(Entity* entity){
	_objectList.push_back(entity);
}


void SceneManager::init(){

	// Objects
	_currentObject = TEAPOT;
	_mappingMode = CUBE_MAPPING;
	createEntities();
	updateMapping();
	changeShader();
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
		_objectList[_currentObject]->draw(_mappingMode);	
		_skybox->draw(_mappingMode);
		

		// LightSource
		GLint ambientGId = ShaderProgram::getInstance()->getId("LightAmbientGlobal");
		glUniform3fv(ambientGId, 1, glm::value_ptr(_ambientGlobal));
		_lightSource->draw();

		ShaderProgram::getInstance()->unBind();
	}
}

void SceneManager::update(){

	// Change Solid type
	if(Input::getInstance()->keyWasReleased('T')) {
		_currentObject = (_currentObject + 1) % NSOLIDS;
		_objectList[_currentObject]->createBufferObjects(_vaoId, _vboId);
	}

	if(Input::getInstance()->keyWasReleased('P')) {
		_mappingMode= (_mappingMode + 1) % NMAPINGS;
		changeShader();
		updateMapping();
		_objectList[_currentObject]->createBufferObjects(_vaoId, _vboId);
		if(_skybox != NULL) {
			_skybox->createBufferObjects(_vaoIdEnv, _vboIdEnv);
		}
	}

	// Exit
	if(Input::getInstance()->keyWasReleased('M')){
		exit(0);
	}

	// Change Materials
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

	// Change Light distance (in each direction)	
	if(Input::getInstance()->keyWasPressed('A')) {
		 _lightSource->decX();
	}
	if(Input::getInstance()->keyWasPressed('D')) {
		 _lightSource->incX();
	}
	if(Input::getInstance()->keyWasPressed('S')) {
		 _lightSource->decY();
	}
	if(Input::getInstance()->keyWasPressed('W')) {
		 _lightSource->incY();
	}	
	if(Input::getInstance()->keyWasPressed('Q')) {
		 _lightSource->decZ();
	}
	if(Input::getInstance()->keyWasPressed('E')) {
		 _lightSource->incZ();
	}

	// Rotate Axis
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



void SceneManager::createBufferObjects(){
	_vaoId = new GLuint[1];
	_vboId = new GLuint[2];
	_vaoIdEnv = new GLuint[1];
	_vboIdEnv = new GLuint[2];

	glGenVertexArrays(1, _vaoId);		//Vertex Array
	glGenBuffers(2, _vboId);			//Buffer Array
	glGenVertexArrays(1, _vaoIdEnv);	//Vertex Array
	glGenBuffers(2, _vboIdEnv);			//Buffer Array

	// Create buffer for specific entity
	_objectList[_currentObject]->createBufferObjects(_vaoId, _vboId);
	if(_skybox != NULL)
		_skybox->createBufferObjects(_vaoIdEnv, _vboIdEnv);
	
	// Reserve space for the Uniform Blocks
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
	glDisableVertexAttribArray(3); //Tangents
}

void SceneManager::destroyBufferObjects(){
	_objectList.clear();
	ShaderProgram::getInstance()->destroyShaderProgram();
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(3, _vboId);
	glDeleteVertexArrays(1, _vboId);

	Camera::getInstance()->~Camera();
}



