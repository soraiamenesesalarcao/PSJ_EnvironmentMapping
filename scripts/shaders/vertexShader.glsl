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

uniform vec3 EyePosition;
uniform vec3 LightPosition;

// Output data /////////////////////////////////////////////////////////////////
out vec2 ex_UV;
out vec3 ex_Normal;
out vec3 ex_HalfVector;
out vec3 ex_LightVector;
out vec3 ex_ViewVector;
out float ex_LightDistance;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	vec4 pos = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	vec3 surfaceToLight, L, V, N;

	surfaceToLight = LightPosition - pos.xyz;
	L = normalize(surfaceToLight);
	V = normalize(EyePosition);
	N = normalize(NormalMatrix * in_Normal.xyz).xyz;

	ex_UV = in_UV;
	ex_Normal = N;
	ex_HalfVector = normalize(L + V);
	ex_LightVector = L;
	ex_ViewVector = V;
	ex_LightDistance = length(surfaceToLight);

	gl_Position = pos;
}