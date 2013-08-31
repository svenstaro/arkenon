#version 130

uniform sampler2D diffuseMap;
uniform sampler2D lightMap;

in vec2 out_TextureCoords;

out vec4 out_Color;

void main() {
    vec3 diffuse = texture(diffuseMap,  out_TextureCoords).xyz ;
	vec3 light = texture(lightMap, out_TextureCoords).xyz;

	out_Color.rgb = diffuse * 0.2;
	out_Color.rgb += diffuse * light;
	out_Color.a   = 1.0;
}
