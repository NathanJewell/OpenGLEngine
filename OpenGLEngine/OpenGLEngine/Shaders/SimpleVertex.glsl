#version 450 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 MVP; //model view projection matrix

out vec4 color;

void main()
{
	color = in_color; //set color to red

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	//last line for check
	gl_Position = MVP*vec4(in_position, 1);
}


