#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D Texture;

void main(){
	vec3 MaterialDiffuseColor = texture( Texture, UV ).rgb;
	color =	MaterialDiffuseColor;

}