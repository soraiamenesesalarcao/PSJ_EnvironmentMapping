#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec3 ex_HalfVector;
in vec3 ex_LightVector;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform sampler2D Texture1;
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

	vec3 Ambient, Diffuse, Specular;
	float Attenuation, NdotH, NdotL;

	vec3 AmbientGlobal = vec3(0.2);

	vec3 textureColor = texture(Texture1, ex_UV).rgb;
	vec3 textureNormal = texture(NormalTexture, ex_UV).rgb; 

	vec3 lightVec = normalize(-ex_LightVector);
	vec3 halfVec = normalize(ex_HalfVector);

	vec3 N = 2.0 * textureNormal - 1.0;
	//N = normalize(N);
	
	color = AmbientGlobal;

	NdotL = max(0.0, dot(N, lightVec));
	Diffuse = MaterialDiffuseColor * LightDiffuse * NdotL;
	Ambient = MaterialAmbientColor * LightAmbient;
		
	if (NdotL > 0){
		NdotH = max(0.0, dot(N, halfVec));
		Specular = MaterialSpecularColor * LightSpecular * pow(NdotH, MaterialShininess);
	} else Specular = vec3(0.0);

	color += Diffuse + Specular + Ambient;
	color *= textureColor;
}