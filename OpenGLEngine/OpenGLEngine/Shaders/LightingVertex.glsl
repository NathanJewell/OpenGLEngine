#version 450 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;
layout(location = 2) in vec3 normal;

uniform mat4 projection_matrix, view_matrix, model_matrix, rotation_matrix;
uniform mat4 MVP; //model view projection matrix
uniform vec3 lightPosition_worldspace;

//light color, power, position
out vec4 color;
out mat4 modelview_matrix;
out vec3 vertex_eyespace;
out vec3 normal_space;

void main()
{
	//translation matrix
	color = vec4(0.0, 0.0, 1.0, 1.0); //set color to red

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	gl_Position = MVP * vec4(in_position,1);
	
	//time to calculate some lighting stuff
	modelview_matrix = view_matrix * rotation_matrix; //use rotation_matrix so it remains uniform
	normal_space = normal; //somespace
	vertex_eyespace = vec3(modelview_matrix) * in_position;
	
	
	
}


