#version 450 core

//This shader allows for all basic vector multiplication changes to create dynamic models
//projection matrix, view matrix, rotation, and translation are all supported

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec4 in_color;

uniform mat4 projection_matrix, view_matrix;
uniform vec3 rotation;
uniform vec3 translation;

out vec4 color;

void main()
{
	color = in_color;
	
	//translation matrix
	mat4 translation = mat4(1.0, 0.0, 0.0, translation.x,
							0.0, 1.0, 0.0, translation.y,
							0.0, 0.0, 1.0, translation.z,
							0.0, 0.0, 0.0, 1.0);
		
	mat4 rotate_x = mat4(1.0, 0.0, 0.0, 0.0,
		0.0, cos(rotation.x), sin(rotation.x), 0.0,
		0.0, -sin(rotation.x), cos(rotation.x), 0.0,
		0.0, 0.0, 0.0, 1.0);

	mat4 rotate_y = mat4(cos(rotation.y), 0.0, -sin(rotation.y), 0.0,
		0.0, 1.0, 0.0, 0.0,
		sin(rotation.y), 0.0, cos(rotation.y), 0.0,
		0.0, 0.0, 0.0, 1.0);

	mat4 rotate_z = mat4(cos(rotation.z), -sin(rotation.z), 0.0, 0.0,
		sin(rotation.z), cos(rotation.z), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);

	//remember the order of multiplication is inverted ie(pos will first be multiplied by rotate_z etc...)
	gl_Position = translation * projection_matrix * view_matrix * rotate_y * rotate_x *rotate_z * vec4(in_position,1);
}


