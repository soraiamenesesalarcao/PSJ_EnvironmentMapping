#version 330 core

// Input vertex data ///////////////////////////////////////////////////////////
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;


// Uniforms ////////////////////////////////////////////////////////////////////

uniform mat4 ModelMatrix;
uniform mat4 NormalMatrix;
layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

// Light components
uniform vec3 LightPosition;
uniform vec3 LightAmbientGlobal;
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 HalfVector;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;

// Output data /////////////////////////////////////////////////////////////////
out vec2 ex_UV;
out vec4 ex_Normal;

// Light components
out vec3 ex_LightAmbientGlobal;
out vec3 ex_LightAmbient;
out vec3 ex_LightDiffuse;
out vec3 ex_HalfVector;
out vec3 ex_LightDirection;
out float ex_LightDistance;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	ex_Normal  = NormalMatrix * in_Normal;

	ex_LightAmbientGlobal = LightAmbientGlobal;
	ex_LightAmbient = MaterialAmbientColor * LightAmbient;
	ex_LightDiffuse = MaterialDiffuseColor * LightDiffuse;	

	// Output position of the vertex, in clip space : ProjectionMatrix * ViewMatrix * ModelMatrix * position
	gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;	
	// UV of the vertex. No special space for this one.
	ex_UV = in_UV;
}