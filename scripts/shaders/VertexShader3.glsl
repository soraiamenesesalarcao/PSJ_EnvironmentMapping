#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec4 in_Position;
layout(location = 1) in vec4 in_Normal;
layout(location = 2) in vec2 in_UV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

uniform vec4 Color;
uniform mat4 ModelMatrix;
layout(std140) uniform SharedMatrices
{
	mat4 ViewMatrix;
	mat4 ProjectionMatrix;
};

//uniform vec3 LightPosition_worldspace;

void main(){

	vec3 LightPosition_worldspace = vec3(0,-5,0);

	// Output position of the vertex, in clip space : ProjectionMatrix * ViewMatrix * ModelMatrix * position
	gl_Position =  ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;
	
	// Position of the vertex, in worldspace : ModelMatrix * position
	Position_worldspace = (ModelMatrix * in_Position).xyz;
	
	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = ( ViewMatrix * ModelMatrix * in_Position).xyz;
	EyeDirection_cameraspace = vec3(0,0,0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. ModelMatrix is ommited because it's identity.
	vec3 LightPosition_cameraspace = ( ViewMatrix * vec4(LightPosition_worldspace,1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;
	
	// Normal of the the vertex, in camera space
	Normal_cameraspace = ( ViewMatrix * ModelMatrix * in_Normal).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	
	// UV of the vertex. No special space for this one.
	UV = in_UV;
}

