#version 460

layout (location = 0) in vec3 position;

uniform mat4 pv_matrix;
uniform mat4 model_matrix;

void main(void)
{
	gl_Position = pv_matrix * model_matrix * vec4(position,1.0);
} 
