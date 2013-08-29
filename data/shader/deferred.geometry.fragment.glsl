#version 130
precision highp float;

in vec4 out_Color;
in vec3 out_Position;
in vec3 out_Normal;
in vec2 out_TextureCoords;

out vec3 color;
out vec3 position;
out vec3 normal;

uniform sampler2D diffuse_texture;
uniform sampler2D normalMap;

void main()
{
	vec3 textureNormal = texture2D(normalMap, out_TextureCoords).xyz;
    color = texture(diffuse_texture, out_TextureCoords).rgb; // no blending here
    position = out_Position;
    normal = normalize(out_Normal + textureNormal);
}
