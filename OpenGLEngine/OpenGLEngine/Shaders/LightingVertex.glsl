#version 450 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 normal;

uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform mat4 MVP; //model view projection matrix
uniform vec3 lightPosition_worldspace;

out vec4 color;
out vec3 lightPosition_cameraspace;
out vec3 lightDirection_cameraspace;
out vec3 normal_cameraspace;
out vec3 fragmentPosition_cameraspace;

void main()
{
	//translation matrix
	vec4 color = vec4(0.0, 0.0, 1.0, 1.0); //set color to red

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	gl_Position = MVP * vec4(in_position,1);
	
	
	
	//time to calculate some lighting stuff
	vec3 vertexPos_worldspace = (model_matrix * vec4(in_position, 1)).xyz; //transforms shape to worldspace (applies translation, rotation)
	vec3 vertexPosition_cameraspace = (view_matrix * model_matrix * vec4(in_position, 1)).xyz;
	vec3 eyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace; //simple distance formula between camera(0, 0, 0) and vertex
	
	vec3 lightPosition_cameraspace = (view_matrix * vec4(lightPosition_worldspace, 1)).xyz;
	vec3 lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;
	
	vec3 normal_cameraspace = (view_matrix * model_matrix * vec4(normal, 0)).xyz;
	
	vec3 fragmentPosition_cameraspace = (view_matrix * vec4(in_position, 1)).xyz;
	
	
}


