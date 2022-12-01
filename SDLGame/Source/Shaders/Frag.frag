#version 430 core

out vec4 color;                                                   

in vec2 UV;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(void)                                                   
{   
    color = mix(texture( texture0, UV ), texture( texture1 , UV ), 0.5); 
}                                                                 