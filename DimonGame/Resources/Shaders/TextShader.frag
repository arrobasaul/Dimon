#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_TextCoord;

uniform sampler2D u_Texture;
uniform vec4 u_Color;
uniform float u_TilingFactor;
void main()
{
    color = texture(u_Texture, v_TextCoord* u_TilingFactor) * u_Color;
}