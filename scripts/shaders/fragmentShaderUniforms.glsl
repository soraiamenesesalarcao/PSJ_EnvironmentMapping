#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec3 ex_LightAmbientGlobal;
in vec3 ex_LightAmbient;
in vec3 ex_LightDiffuse;
in vec3 ex_HalfVector;
in vec3 ex_LightDirection;
in float ex_LightDistance;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform sampler2D Texture1;
uniform sampler2D Texture2;

// Light components
uniform vec3 LightSpecular;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;
uniform float MaterialShininess;

// Attenuation
uniform float LightLinearAttenuation;
uniform float LightQuadraticAttenuation;
uniform float LightCubicAttenuation;

// Output data /////////////////////////////////////////////////////////////////
out vec3 color;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	//vec3 textureColor = texture( Texture, UV ).rgb;
	vec3 textureColor = texture( Texture1, ex_UV ).rgb * texture( Texture2, ex_UV ).rgb;

	//color =	textureColor + MaterialAmbientColor + MaterialDiffuseColor + MaterialSpecularColor * pow(1, MaterialShininess);
	//color =	textureColor + MaterialSpecularColor * pow(1, MaterialShininess);
	color =	textureColor + ex_LightDiffuse + ex_LightAmbientGlobal;
}