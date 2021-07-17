#version 460

out vec4 color;

void main(void)
{	
	color = vec4(((gl_PrimitiveID * 8003 + 37) % 255) / 255.0, ((gl_PrimitiveID * 4001 + 53) % 255) / 255.0,((gl_PrimitiveID * 6007 + 223) % 255 ) / 255.0, 1);
}
