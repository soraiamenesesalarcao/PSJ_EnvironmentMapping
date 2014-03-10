#version 330 core

// Input vertex data ///////////////////////////////////////////////////////////
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;

// Uniforms ////////////////////////////////////////////////////////////////////
uniform mat4 ModelMatrix;
uniform mat3 NormalMatrix;
layout(std140) uniform SharedMatrices {
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

// Light components
uniform vec3 EyePosition;
uniform vec3 LightPosition;
uniform vec3 LightAmbientGlobal;
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 LightSpecular;
uniform vec3 HalfVector;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;

// Output data /////////////////////////////////////////////////////////////////
out vec2 ex_UV;
out vec3 ex_Normal;

// Light components
out vec3 ex_AmbientGlobal;
out vec3 ex_Ambient;
out vec3 ex_Diffuse;
out vec3 ex_Specular;
out vec3 ex_HalfVector;
out vec3 ex_LightDirection;
out float ex_LightDistance;

// Cube Mapping
out vec3 ex_Reflect;



// Main ////////////////////////////////////////////////////////////////////////

void main(){

	vec4 pos = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	vec3 surfaceToLight, L, V, N;

	// Distance, Halfvector, Direction
	surfaceToLight = LightPosition - pos.xyz;
	ex_LightDistance = length(surfaceToLight);
	L = normalize(surfaceToLight); // fica
	V = normalize(EyePosition);
	ex_HalfVector = normalize(L + V); // fica
	ex_LightDirection = L;
	N = normalize(NormalMatrix * in_Normal.xyz).xyz;
	ex_Normal = N;
	ex_Reflect = reflect(V, N).xyz;

	// Components
	ex_AmbientGlobal = LightAmbientGlobal * MaterialAmbientColor;
	ex_Ambient = MaterialAmbientColor * LightAmbient;
	ex_Diffuse = MaterialDiffuseColor * LightDiffuse;
	ex_Specular = MaterialSpecularColor * LightSpecular;	

	gl_Position = pos;
	
	ex_UV = in_UV;
}