#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNorm;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 projection_matrix;
out vec2 texcoord;

void main()
{
    gl_Position = projection_matrix * vec4(aPos.x, aPos.y, aPos.z,  1.0);
    texcoord = aTexCoord;
}
