#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec3 ex_Normal;
in vec3 ex_AmbientGlobal;
in vec3 ex_Ambient;
in vec3 ex_Diffuse;
in vec3 ex_Specular;
in vec3 ex_HalfVector;
in vec3 ex_LightDirection;
in vec3 ex_Reflect;
in float ex_LightDistance;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform samplerCube CubeMap;
//uniform sampler2D Texture1;

// Material components
uniform float MaterialShininess;

// Attenuation
uniform float LightConstantAttenuation;
uniform float LightLinearAttenuation;
uniform float LightQuadraticAttenuation;

//Control illumination
uniform int Illumination;

// Output data /////////////////////////////////////////////////////////////////
out vec3 color;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

// Multi-Texture
//	vec3 textureColor = texture(Texture1, ex_UV).rgb;
	vec3 textureCube = texture(CubeMap, ex_Reflect).rgb;

	color = ex_AmbientGlobal;

	if(Illumination == 1) {
		float attenuation, NdotH, NdotL;
		vec3 N;	

		// Light and Material
	
		attenuation = 1.0 / ( LightConstantAttenuation
							+ LightLinearAttenuation * ex_LightDistance 
							+ LightQuadraticAttenuation * pow(ex_LightDistance, 2.0) );
		N = ex_Normal;
		NdotH = max(dot(N, ex_HalfVector), 0.0);
		NdotL = max(dot(N, ex_LightDirection), 0.0);

		if(NdotL > 0.0) color += attenuation * (ex_Diffuse * NdotL + ex_Ambient);		
		else color += attenuation * (ex_Diffuse + ex_Ambient);

		color += attenuation * ex_Specular * pow(NdotH, MaterialShininess);
		color *= textureCube;
	} else color = textureCube;
}