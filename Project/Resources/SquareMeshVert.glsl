#version 460

layout (location = 0) in vec2 square_pos;

uniform mat4 mv_matrix;
uniform mat4 proj_matrix;

void main(void)
{
	gl_Position = proj_matrix * mv_matrix * vec4(square_pos.x, square_pos.y, 0.0, 1.0);
} 
