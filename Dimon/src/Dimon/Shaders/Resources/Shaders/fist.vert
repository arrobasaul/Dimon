#version 330

layout(location = 0) in vec3 inVertexPosition;

out vec2 passTextureCoord;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

void main()
{
    gl_Position =  vec4(inVertexPosition, 1.0);
}
