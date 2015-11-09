#version 450 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;


uniform mat4 projection_matrix, view_matrix, model_matrix;
uniform mat4 MVP; //model view projection matrix
uniform vec3 lightPosition_worldspace;

out vec4 color;

void main()
{
	//translation matrix
	vec4 color = vec4(0.0, 0.0, 1.0, 1.0); //set color to red

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	gl_Position = vec4(in_position,1);//MVP * vec4(in_position,1);

}


