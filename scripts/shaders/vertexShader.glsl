#version 330 core

// Input vertex data ///////////////////////////////////////////////////////////
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;
layout(location = 3) in vec4 in_Tangent;

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
	vec3 surfaceToLight, L, V, N, T, B;

	surfaceToLight = LightPosition - pos.xyz;
	L = normalize(surfaceToLight);
	V = normalize(EyePosition);
	N = normalize(NormalMatrix * in_Normal.xyz).xyz;

	ex_UV = in_UV;
	ex_Normal = N;
	ex_HalfVector = normalize(L + V);
	ex_LightVector = L;

	ex_LightDistance = length(surfaceToLight);

	// Contas para o Cube Mapping
	vec4 pos2 = ViewMatrix * ModelMatrix * in_Position;
	ex_ViewVector = normalize(pos2.xyz);

	// Contas para o Bump Mapping
	// T = normalize(NormalMatrix, in_Tangent.xyz).xyz;
	// B = in_Tangent.w * cross(N, T);
	// vec3 lightDirection2 = normalize(LightPosition - pos2.xyz);
	//vec3 v = (dot(lightDirection2, T), dot(lightDirection2, B), dot (lightDirection2, N));
	//ex_LightVector = normalize(v);
	//pos2 = normalize(pos2);

	//vec3 halfVector = normalize(pos2 + lightDirection2).xyz; // ver se faz diferença
	//vec3 v2 = (dot (halfVector, T), dot (halfVector, B), dot (halfVector, N));
	//ex_HalfVector = normalize(v2);

	// Contas para o Sphere Mapping
	//vec3 U = normalize(ViewMatrix * ModelMatrix * in_Position);
	//vec3 R = reflect(U, N);
	//float m = 2.0 * sqrt(pow(R.x, 2.0) + pow(R.y, 2.0) + pow(R.z + 1.0, 2.0));
	//ex_UV[1].s = R.x/m + 0.5;
	//ex_UV[1].t = R.y/m + 0.5;

	gl_Position = pos;
}