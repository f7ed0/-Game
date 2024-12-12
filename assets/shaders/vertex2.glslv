#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aCol;

uniform uint time;

out vec3 ourColor;

void main()
{
    float acoef = sin(time * 0.001f) * 1.0f;
    gl_Position = vec4(aPos.x * (1 + sin(time * 0.001f)) , aPos.y * ( 1 + sin(time * 0.001f)), aPos.z,  1.0);
    ourColor = aCol;
}
