#version 130
precision highp float;

uniform sampler2D diffuseMap;
uniform sampler2D lightMap;
uniform sampler2D shadowMap;
uniform sampler2D lambertMap;

uniform float time;

in vec2 out_TextureCoords;

out vec4 out_Color;

const vec4 ambientGlobal = vec4(0.05, 0.05, 0.05, 1.0);

void main() {
	float colorFactor = 0.1;
    vec4 albedo = texture(diffuseMap,  out_TextureCoords);
	vec4 pointLight = texture(lightMap, out_TextureCoords);
	float ssao = texture(shadowMap, out_TextureCoords).x;

	vec4 ambient = ambientGlobal;
	vec4 lightContribution = vec4(0.0, 0.0, 0.0, 1.0);
	lightContribution += pointLight;

	vec4 final_color = (ambient * ssao + lightContribution) * albedo;
	out_Color = vec4(final_color.rgb, 1.0);
}
