#version 450 core

layout(location = 0) out vec4 out_color;

uniform vec3 lightColor;
uniform float lightPower;
uniform vec3 diffuseColor, ambientColor; //material's ambient and diffuse colors

in vec4 color;


void main(void)
{
	out_color = color
}