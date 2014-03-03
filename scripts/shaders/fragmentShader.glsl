#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;

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

	vec3 textureColor = texture( Texture1, UV ).rgb * texture( Texture2, UV ).rgb;
	color =	textureColor + MaterialSpecularColor * pow(1, MaterialShininess);

}