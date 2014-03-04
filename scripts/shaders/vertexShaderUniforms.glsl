#version 150

// Input vertex data ///////////////////////////////////////////////////////////
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;


// Uniforms ////////////////////////////////////////////////////////////////////

uniform vec3 EyePosition;
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
uniform vec3 LightSpecular;
uniform vec3 HalfVector;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;

// Output data /////////////////////////////////////////////////////////////////
out vec2 ex_UV;
out vec4 ex_Normal;

// Light components
out vec3 ex_AmbientGlobal;
out vec3 ex_Ambient;
out vec3 ex_Diffuse;
out vec3 ex_Specular;
out vec3 ex_HalfVector;
out vec3 ex_LightDirection;
out float ex_LightDistance;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	vec4 pos = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

	// Distance, Halfvector, Direction

	//vec3 surfaceToLight = LightPosition - in_Position.xyz;

	vec3 surfaceToLight = LightPosition - pos.xyz;

	ex_LightDistance = length(surfaceToLight);

	vec3 L = normalize(surfaceToLight);
	vec3 V = normalize(-EyePosition);
	ex_HalfVector = normalize(L + V);

	ex_LightDirection = L;

	ex_Normal  = NormalMatrix *  in_Normal;

	// Components
	ex_AmbientGlobal = LightAmbientGlobal * MaterialAmbientColor;
	ex_Ambient = MaterialAmbientColor * LightAmbient;
	ex_Diffuse = MaterialDiffuseColor * LightDiffuse;
	ex_Specular = MaterialSpecularColor * LightSpecular;	

	// Output position of the vertex, in clip space : ProjectionMatrix * ViewMatrix * ModelMatrix * position
	//gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;	
	gl_Position = pos;
	// UV of the vertex. No special space for this one.
	ex_UV = in_UV;
}