#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec3 ex_HalfVector;
in vec3 ex_LightVector;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform sampler2D Texture2D;
uniform sampler2D NormalTexture;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;
uniform float MaterialShininess;

// Light + Attenuation
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 LightSpecular;

// Output data /////////////////////////////////////////////////////////////////
out vec3 color;


// Main ////////////////////////////////////////////////////////////////////////
void main(){

	vec3 AmbientGlobal, Ambient, Diffuse, Specular, textureColor, textureNormal;
	vec3 lightVec, halfVec, N
	float Attenuation, NdotH, NdotL;

	AmbientGlobal = vec3(0.2); // receber?

	textureColor = texture(Texture2D, ex_UV).rgb;
	textureNormal = texture(NormalTexture, ex_UV).rgb; 

	lightVec = normalize(-ex_LightVector);
	halfVec = normalize(ex_HalfVector);

	N = 2.0 * textureNormal - 1.0;
	
	color = AmbientGlobal;

	NdotL = max(0.0, dot(N, lightVec));
	Diffuse = MaterialDiffuseColor * LightDiffuse * NdotL;
	Ambient = MaterialAmbientColor * LightAmbient;
		
	if (NdotL > 0){
		NdotH = max(0.0, dot(N, halfVec));
		Specular = MaterialSpecularColor * LightSpecular * pow(NdotH, MaterialShininess);
	}
	else Specular = vec3(0.0);

	color += Diffuse + Specular + Ambient;
	color *= textureColor;
}