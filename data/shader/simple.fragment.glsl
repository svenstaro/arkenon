#version 130
precision highp float; // Video card drivers require this line to function properly

in vec2 out_TextureCoords;
in vec4 out_Color;
in vec3 out_Normal;

out vec4 fragColor;

uniform vec4 ambient_light;

void main()
{
    fragColor = out_Color * ambient_light;
}
