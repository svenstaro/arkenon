#version 130
precision highp float; // Video card drivers require this line to function properly

in vec2 out_TextureCoords;
in vec4 out_Color;
in vec3 out_Normal;

out vec4 fragColor;

void main()
{
    fragColor = vec4(out_Color.rgb * (out_Normal.x * -out_Normal.z), out_Color.a);
}
