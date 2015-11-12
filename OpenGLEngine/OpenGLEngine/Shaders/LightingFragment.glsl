#version 410 core
#define USE_HALF_VECTOR 1

layout(location = 3) in vec2 uv;
 
uniform mat4 view_matrix;
uniform vec4 lightColor;
uniform vec4 diffuseColor;
uniform vec4 ambientColor;
uniform vec4 specularColor;
uniform sampler2D tex2d;

in vec4 backup_color;
in mat4 modelview_matrix;
in vec3 vertex_worldspace;
in vec3 normal_cameraspace;
in vec3 normal_o;
in vec3 eyeDirection_cameraspace;
in vec3 lightDirection_cameraspace;

out vec4 out_color;

void main(void)
{
	vec4 color = backup_color;
		
	vec3 normal_n = normalize(normal_cameraspace);
	vec3 lightDirection_n = normalize(lightDirection_cameraspace);

	vec4 c_ambientColor = vec4(.1, .1, .1, 1) * color;
	
	float cosTheta = clamp(dot(normal_n, lightDirection_n), 0, 1);
	
	vec3 camDirection_cameraspace = normalize(eyeDirection_cameraspace);
	vec3 normal_reflect = reflect(-lightDirection_n, normal_n);
	float cosAlpha = clamp(dot(camDirection_cameraspace, normal_reflect), 0, 1);
	
	
	out_color = color * lightColor * cosTheta + specularColor * color * lightColor * pow(cosAlpha, 5);
	
}

/*
	vec3 spec = vec3(0.0);
	vec3 normal_eyespace = normalize(mat3(modelview_matrix)*normal_objectspace); //transform normal to eyespace
	
	//diffuse
	vec3 s = vec3(1.0, 1.0, 1.0);
	float sdn = max(dot(normal_eyespace, s), 0.0);
	
#if USE_HALF_VECTOR
	vec3 v = normalize(-vertex_eyespace);
	vec3 h = normalize(v + s);
	if(sdn > 0.0)
	{
		spec = pow(max(dot(h,normal_eyespace),0.0),13.0) * vec3(1.0,0.0,1.0) * 5;
	}
#else
	vec3 v = normalize(-vertex_eyespace);
	vec3 r = reflect(-s, normal_eyespace);
	if(sdn > 0.0)
	{
		spec = pow(max(dot(r,v),0.0),3.0) * vec3(1.0,0.0,1.0);
	}
#endif
	
	out_color.rgb = vec3(0.0, 0.2, 0.6) * sdn + 0.4 * spec;
	out_color.a = 1.0;
*/