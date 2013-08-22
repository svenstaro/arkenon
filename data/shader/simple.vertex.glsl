#version 130
in vec3 in_Position;
in vec2 in_TextureCoords;
in vec4 in_Color;
in vec3 in_Normal;

out vec2 out_TextureCoords;
out vec4 out_Color;
out vec3 out_Normal;

uniform mat4 MVP;

void main(){
    vec4 v = vec4(in_Position, 1);
    gl_Position = MVP * v;

    out_TextureCoords = in_TextureCoords;
    out_Color = in_Color;
    out_Normal = in_Normal;
}
