#version 450 core

layout(location = 0) out vec4 out_color;

uniform vec3 lightColor;
uniform float lightPower;
uniform vec3 diffuseColor, ambientColor; //material's ambient and diffuse colors

in vec4 color;
in vec3 fragmentPosition_cameraspace;
in vec3 normal_cameraspace;
in vec3 lightDirection_cameraspace;
in vec3 lightPosition_cameraspace;

void main(void)
{
	vec3 n = normalize(normal_cameraspace);
	vec3 l = normalize(lightDirection_cameraspace);
	
	float cosTheta = clamp(dot(n,l),0,1);
	
	vec3 slope = abs(fragmentPosition_cameraspace-lightPosition_cameraspace);
	float distance2 = slope.x*slope.x + slope.y*slope.y + slope.z*slope.z;
	
	out_color = vec4(((diffuseColor * lightColor * lightPower * cosTheta) /(distance2)),1.0)*color;
}