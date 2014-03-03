#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

uniform vec4 Color;
uniform mat4 ModelMatrix;
layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

void main(){
	// Output position of the vertex, in clip space : ProjectionMatrix * ViewMatrix * ModelMatrix * position
	gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	
	// UV of the vertex. No special space for this one.
	UV = in_UV;
}