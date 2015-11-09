#version 450 core
#define USE_HALF_VECTOR 1


uniform mat4 view_matrix;

in vec4 color;
in vec3 normal_space;
in mat4 modelview_matrix;
in vec3 vertex_eyespace;

out vec4 out_color;

void main(void)
{
	vec3 spec = vec3(1.0);
	vec3 normal_eyespace = normalize(mat3(modelview_matrix) * normal_space);
	out_color.rgb =  vec3(color) * normalize(normal_eyespace);
	out_color.a = 1.0;
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