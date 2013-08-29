#version 130
in vec3 in_Position;
in vec2 in_TextureCoords;
in vec4 in_Color;
in vec3 in_Normal;

out vec3 out_Position;
out vec2 out_TextureCoords;
out vec4 out_Color;
out vec3 out_Normal;

uniform mat4 MVP;
uniform mat4 M;

void main()
{
    out_Position = (M * vec4(in_Position, 1.f)).xyz;
    out_TextureCoords = in_TextureCoords;
    out_Color = in_Color;
    out_Normal = (M * vec4(in_Normal, 0.0)).xyz;
    gl_Position = MVP * vec4(in_Position, 1.0);
}
