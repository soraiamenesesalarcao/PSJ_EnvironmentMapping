#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D Texture;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;
uniform float MaterialShininess;

void main(){

	vec3 textureColor = texture( Texture, UV ).rgb;


	//color =	textureColor + MaterialAmbientColor + MaterialDiffuseColor + MaterialSpecularColor * pow(1, MaterialShininess);
	color =	textureColor + MaterialSpecularColor * pow(1, MaterialShininess);

}