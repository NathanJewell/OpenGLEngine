#version 410 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 normal;
//layout(location = 3) in vec2 uv;

uniform mat4 projection_matrix, view_matrix, model_matrix, rotation_matrix;
uniform mat4 MVP; //model view projection matrix
uniform vec3 lightPosition_worldspace;
//uniform sampler2d tex2d;

//light color, power, position
out vec4 backup_color;
out mat4 modelview_matrix;
out vec3 vertex_worldspace;
out vec3 normal_cameraspace;
out vec3 normal_o;
out vec3 eyeDirection_cameraspace;
out vec3 lightDirection_cameraspace;
out vec3 lightPosition_cameraspace;


void main()
{
//in_color = texture2d(tex2d, gl_TexCoord[0].st)
	//translation matrix
	backup_color = vec4(0.0, 0.0, 1.0, 1.0); //set color to red
	//color = vec4(normal, 1);

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	gl_Position = MVP * vec4(in_position,1);
	
	//time to calculate some lighting stuff
	modelview_matrix = view_matrix * rotation_matrix; //use rotation_matrix so it remains uniform
	//vertex_eyespace = vec3(modelview_matrix) * in_position;
	
	normal_o = (modelview_matrix * vec4(normal, 0.0)).xyz; //convert to world coords
	
	vertex_worldspace = (model_matrix * vec4(in_position, 1)).xyz; //transform coordinate to model space
	vec3 vertex_cameraspace = (view_matrix * model_matrix * vec4(vertex_worldspace, 1.0)).xyz;
	eyeDirection_cameraspace = vec3(0.0, 0.0, 0.0) - vertex_cameraspace;
	
	lightPosition_cameraspace = (view_matrix * vec4(lightPosition_worldspace, 1)).xyz; //convert light position to cameraspace
	lightDirection_cameraspace = lightPosition_cameraspace + eyeDirection_cameraspace;
	
	normal_cameraspace = (modelview_matrix * vec4(normal, 0)).xyz;
	
	
	
}


