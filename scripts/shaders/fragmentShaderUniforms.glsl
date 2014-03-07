#version 330 core

// Interpolated values /////////////////////////////////////////////////////////
in vec2 ex_UV;
in vec4 ex_Normal;
in vec3 ex_AmbientGlobal;
in vec3 ex_Ambient;
in vec3 ex_Diffuse;
in vec3 ex_Specular;
in vec3 ex_HalfVector;
in vec3 ex_LightDirection;
in float ex_LightDistance;

// Uniforms ////////////////////////////////////////////////////////////////////

// Textures
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform samplerCube Texture3;

// Material components
uniform float MaterialShininess;

// Attenuation
uniform float LightConstantAttenuation;
uniform float LightLinearAttenuation;
uniform float LightQuadraticAttenuation;


// Output data /////////////////////////////////////////////////////////////////
out vec3 color;

// Main ////////////////////////////////////////////////////////////////////////

void main(){

	float attenuation;
	color = ex_AmbientGlobal;

	// Multi-Texture
	vec3 textureColor = texture( Texture1, ex_UV ).rgb * 
						texture( Texture2, ex_UV ).rgb;

	// Light and material

	attenuation = 1.0 / ( LightConstantAttenuation
						+ LightLinearAttenuation * ex_LightDistance 
						+ LightQuadraticAttenuation * pow(ex_LightDistance, 2.0) );

	vec3 N = normalize(ex_Normal).xyz;
	float NdotH = max(dot(N, ex_HalfVector), 0.0);
	float NdotL = max(dot(N, ex_LightDirection), 0.0);

	if(NdotL > 0.0) {		
		color += attenuation * (ex_Diffuse * NdotL + ex_Ambient);		
	}	else {
		color += attenuation * (ex_Diffuse + ex_Ambient);	
	}

	color += attenuation * ex_Specular * pow(NdotH, MaterialShininess);
	//color *= textureColor;
}