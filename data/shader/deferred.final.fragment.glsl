#version 130
precision highp float;

uniform sampler2D diffuseMap;
uniform sampler2D lightMapMultiply;
uniform sampler2D lightMapAdd;

uniform float time;

in vec2 out_TextureCoords;

out vec4 out_Color;

const vec4 ambientGlobal = vec4(0.05, 0.05, 0.05, 1.0);

void main() {
    vec4 albedo = texture(diffuseMap,  out_TextureCoords);
    vec4 lightFactor = texture(lightMapMultiply, out_TextureCoords);
    vec4 lightAddend = texture(lightMapAdd, out_TextureCoords);

    vec4 final_color = ambientGlobal * albedo + lightFactor * albedo + lightAddend;

    out_Color = vec4(final_color.rgb, 1.0);
    //out_Color = vec4(lightAddend.rgb, 1.0);
}
