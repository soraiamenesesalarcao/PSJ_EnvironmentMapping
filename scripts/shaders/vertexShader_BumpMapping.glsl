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
uniform vec3 LightPosition;

// Output data /////////////////////////////////////////////////////////////////
out vec2 ex_UV;
out vec3 ex_HalfVector;
out vec3 ex_LightVector;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	vec3 N, T, B, v, v2, lightDirection2, halfVector;

	gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	ex_UV = in_UV;

	vec4 pos = ViewMatrix * ModelMatrix * in_Position;

	N = normalize(NormalMatrix * in_Normal.xyz).xyz;
	T = normalize(NormalMatrix * in_Tangent.xyz).xyz;
	B = in_Tangent.w * cross(N, T);

	lightDirection2 = normalize(LightPosition - pos.xyz);
	v.x = dot(lightDirection2, T);
	v.y = dot(lightDirection2, B);
	v.z = dot(lightDirection2, N);
	ex_LightVector = v;

	pos = normalize(pos);
	halfVector = normalize(pos.xyz + lightDirection2).xyz;
	v2.x = dot(halfVector, T);
	v2.y = dot(halfVector, B);
	v2.z = dot(halfVector, N);
	ex_HalfVector = v2;

}