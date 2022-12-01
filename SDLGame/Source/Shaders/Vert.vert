#version 430 core

layout(location = 0) in vec3 VertPos;
layout(location = 1) in vec2 UVs;

out vec2 UV;


void main(void)                                                   
{                                             
	UV = UVs;
	gl_Position.xyz =  VertPos;
	gl_Position.w = 1.0;
}         