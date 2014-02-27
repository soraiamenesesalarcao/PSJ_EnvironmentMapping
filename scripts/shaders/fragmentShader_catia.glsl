#version 330 core

in vec4 ex_Color;
in vec2 ex_UV;
out vec4 out_Color;

uniform sampler2D Textura;

void main(void)
{
        out_Color = texture(Textura, ex_UV) + ex_Color;
}