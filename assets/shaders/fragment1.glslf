#version 440 core
out vec4 FragColor;
in vec2 texcoord;
uniform sampler2D ourTex;

void main()
{
    FragColor = texture(ourTex,texcoord);
} 
