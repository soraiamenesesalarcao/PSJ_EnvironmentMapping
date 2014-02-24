#version 330 core

// In
in vec4 out_Color
in vec3 out_Normal
in vec3 out_Position
in vec2 out_Texcoord;

// Out
out vec4 out_Color_Final;

// Light Attributes
uniform vec3 light_Position;
uniform vec3 light_Ambient;
uniform vec3 light_Diffuse;
uniform vec3 light_Specular;
uniform float light_Distance;
uniform float light_ConstantAttenuation; 
uniform float light_LinearAttenuation;
uniform float light_QuadraticAttenuation;


// Material Attributes
uniform vec3 material_Ambient;
uniform vec3 material_Diffuse;
uniform vec3 material_Specular;
uniform float material_Shininess;

// Camera View Vector
uniform vec3 EyeDirection;

// Matrices
uniform mat4 mtx_Model;
layout(std140) uniform Matrices{
	mat4 mtx_View;
	mat4 mtx_Projection;
};

void main(void) {

	// Phong Shading + Blinn-Phong Illumination + Depth Cueing
	vec3 L = normalize(vec3(mtx_View * vec4(light_Position, 1.0)) - ex_Position); //sem view -> luz segue camara, com view -> luz segue cena
	vec3 N = normalize(out_Normal);
	//vec3 V = normalize(-EyeDirection);
	vec3 V = normalize(-LightPosition);
	vec3 H = normalize(L + V);

	// Ambient Component
	vec3 comp_Ambient = material_Ambient * light_Ambient;

	// Diffuse Component	
	float NdotL = max(dot(N, L), 0.0);
	vec3 comp_Diffuse = material_Diffuse * light_Diffuse * NdotL;

	// Specular Component (Blinn-Phong)
	vec3 specular = vec3(0.0);
	if(NdotL > 0) {
		float NdotH = max(dot(N, H), 0.0);
		specular = material_Specular * light_Specular * pow(NdotH, material_Shininess);
	}

	// Depth Cueing	
	depth_Cueing = light_ConstantAttenuation + 
				   light_LinearAttenuation * light_Distance +
				   light_QuadraticAttenuation * pow(light_Distance, 2);

	// Final
	vec4 lightIntensity = vec4( comp_Ambient + (comp_Diffuse + comp_Specular)/depth_Cueing, 1.0);
	out_Color = LightIntensity
}