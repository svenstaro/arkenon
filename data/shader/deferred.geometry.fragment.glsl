#version 130
precision highp float;

in vec3 var_position;
in vec2 var_textureCoords;
in vec4 var_color;
in vec3 var_normal;
in vec3 var_tangent;
in vec3 var_bitangent;

out vec3 color;
out vec3 position;
out vec3 normal;

uniform sampler2D diffuse_texture;
uniform sampler2D normalMap;

void main()
{
	//mat4 tangentToWorld = transpose(mat3(var_tangent, var_bitangent, var_normal));

	position = var_position;  
    color = texture(diffuse_texture, var_textureCoords).rgb * var_color.rgb; 

	vec3 ts_normal= texture(normalMap, var_textureCoords).xyz * 2.0 - 1.0;
	vec3 ws_normal = var_tangent * ts_normal.x + var_bitangent * ts_normal.y + var_normal * ts_normal.z;

    normal = vec3(var_normal * 0.5 + 0.5);
 }
