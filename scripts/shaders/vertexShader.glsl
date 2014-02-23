#version 330 core

// In
in vec4 in_Color
in vec3 in_Normal
in vec3 in_Position
in vec2 in_Texcoord;

// Out
out vec4 out_Color
out vec3 out_Normal
out vec3 out_Position
out vec2 out_Texcoord;

// Matrices
uniform mat4 mtx_Model;
uniform mat3 mtx_Normal;
layout(std140) uniform Matrices {
	mat4 mtx_Projection;
	mat4 mtx_View;
};

void main(void){
	out_Color = in_Color;
	out_Normal = normalize(mtx_Normal * in_Normal);
	out_Position = vec3(mtx_View * mtx_Model * vec4(in_Position, 1.0));
	out_Texcoord = in_Texcoord;
	gl_Position = mtx_Projection * mtx_View * mtx_Model * vec4(in_Position,1.0);
}