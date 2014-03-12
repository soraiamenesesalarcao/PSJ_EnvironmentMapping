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
out float ex_LightDistance;


// Main ////////////////////////////////////////////////////////////////////////
void main(){
	
	vec4 pos, pos2; 
	vec3 surfaceToLight, L, V, N, U, R;
	float m;

	pos = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	surfaceToLight = LightPosition - pos.xyz;
	L = normalize(surfaceToLight);
	V = normalize(EyePosition);
	N = normalize(NormalMatrix * in_Normal.xyz).xyz;

	pos2 = ViewMatrix * ModelMatrix * in_Position;
	U = normalize(pos2.xyz);
	R = reflect(U, N);
	m = 2.0 * sqrt(2*(R.z + 1));

	ex_UV = vec2(R.x/m + 0.5, -R.y/m + 0.5);
	ex_Normal = N;
	ex_HalfVector = normalize(L + V);
	ex_LightVector = L;
	ex_LightDistance = length(surfaceToLight);

	gl_Position = pos;
}