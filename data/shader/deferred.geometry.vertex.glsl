#version 130
in vec3 in_Position;
in vec2 in_TextureCoords;
in vec4 in_Color;
in vec3 in_Normal;
in vec3 in_Tangent;

out vec3 var_position;
out vec2 var_textureCoords;
out vec4 var_color;
out vec3 var_normal;
out vec3 var_tangent;
out vec3 var_bitangent;


uniform mat4 M;
uniform mat4 MVP;

uniform mat4 normalMatrix; //transpose(inverse(MV)

void main()
{
	gl_Position = MVP * vec4(in_Position, 1.f);

	var_normal = normalize((normalMatrix * vec4(in_Normal, 0.0)).xyz);
    var_position = (M * vec4(in_Position, 1.f)).xyz;

    var_tangent = normalize((normalMatrix * vec4(in_Tangent, 0.0)).xyz);
    var_bitangent = normalize(cross(var_tangent, var_normal));

    var_textureCoords = in_TextureCoords;

    var_color = in_Color;
}
