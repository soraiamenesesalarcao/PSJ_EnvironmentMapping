#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec3 ex_Normal;
in vec3 ex_HalfVector;
in vec3 ex_LightVector;
in vec3 ex_ViewVector;
in float ex_LightDistance;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform samplerCube CubeMap;

// Material components
uniform vec3 MaterialAmbientColor;
uniform vec3 MaterialDiffuseColor;
uniform vec3 MaterialSpecularColor;
uniform float MaterialShininess;

// Light + Attenuation
uniform vec3 LightAmbientGlobal;
uniform vec3 LightAmbient;
uniform vec3 LightDiffuse;
uniform vec3 LightSpecular;
uniform float LightConstantAttenuation;
uniform float LightLinearAttenuation;
uniform float LightQuadraticAttenuation;

// Control illumination
uniform int Illumination;

// Output data /////////////////////////////////////////////////////////////////
out vec3 color;


// Main ////////////////////////////////////////////////////////////////////////
void main(){

	vec3 AmbientGlobal, Ambient, Diffuse, Specular, Reflect, textureCube, textureCubeSky;
	
	AmbientGlobal = MaterialAmbientColor * LightAmbientGlobal;
	Reflect = reflect(ex_ViewVector, ex_Normal).xyz;
	textureCube = texture(CubeMap, Reflect).rgb;
	textureCubeSky = texture(CubeMap, ex_Normal).rgb;

	color = AmbientGlobal;

	if(Illumination == 1) {
		float Attenuation, NdotH, NdotL;

		// Light and Material
		Attenuation = 1.0 / ( LightConstantAttenuation
							+ LightLinearAttenuation * ex_LightDistance 
							+ LightQuadraticAttenuation * pow(ex_LightDistance, 2.0) );
		NdotL = max(dot(ex_Normal, ex_LightVector), 0.0);

		Ambient = MaterialAmbientColor * LightAmbient;
		Diffuse = MaterialDiffuseColor * LightDiffuse * NdotL;

		if (NdotL > 0){
			NdotH = max(dot(ex_Normal, ex_HalfVector), 0.0);
			Specular = MaterialSpecularColor * LightSpecular * pow(NdotH, MaterialShininess);
		} 
		else Specular = vec3(0.0);

		color += Attenuation * (Diffuse + Specular + Ambient);
		color *= textureCube;
	} 
	else color = textureCubeSky;
}