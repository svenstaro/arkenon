#version 130
in vec3 in_Position;
in vec2 in_TextureCoords;
in vec4 in_Color;
in vec3 in_Normal;
in vec3 in_Tangent;
in vec3 in_Bitangent;

out vec3 var_position;
out vec2 var_textureCoords;
out vec4 var_color;
out vec3 var_normal;
out vec3 var_tangent;
out vec3 var_bitangent;

uniform mat4 M;
uniform mat4 MV;
uniform mat4 MVP;
uniform mat3 M3x3;

void main()
{
    var_position = (M * vec4(in_Position, 1.f)).xyz;
    var_textureCoords = in_TextureCoords;
    var_color = in_Color;

    // rotate normals & tangents into world space
    var_normal = normalize(M3x3 * in_Normal);
    var_tangent = normalize((M3x3 * vec3(in_Tangent)).xyz);
    var_bitangent = normalize((M3x3 * vec3(in_Bitangent)).xyz);

    gl_Position = MVP * vec4(in_Position, 1.f);
}
