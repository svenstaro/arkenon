#version 130
precision highp float;

in vec2 out_TextureCoords;
in vec4 out_Color;
in vec3 out_Normal;
in vec3 out_Position;

out vec4 fragColor;

uniform vec3 light_position;
uniform vec4 light_color;
uniform float light_size;

void main()
{
    vec3 diff = light_position - out_Position;
    float strength = 1.f - length(diff) / light_size;
    vec4 col = strength * strength * light_color * dot(out_Normal, diff);
    fragColor = vec4(col.rgb, 1.f);
}
