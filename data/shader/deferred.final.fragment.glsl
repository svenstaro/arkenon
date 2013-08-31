#version 130
precision highp float;

uniform sampler2D diffuseMap;
uniform sampler2D lightMap;
uniform sampler2D shadowMap;
uniform sampler2D lambertMap;

uniform float time;

in vec2 out_TextureCoords;

out vec4 out_Color;


void main() {
	float colorFactor = 0.1;
    vec3 diffuse = texture(diffuseMap,  out_TextureCoords).xyz ;
	vec3 light = texture(lightMap, out_TextureCoords).xyz;
	float shadow = texture(shadowMap, out_TextureCoords).x;


	//vec3 globalLight = texture(lambertMap, vec2(0.5 * shadow , 1.0*0.9)).xyz;

	float ambient = 0.1;

	//vec3 col = (diffuse * 0.5) + (diffuse * light) * (diffuse * shadow );
	vec3 col =  ambient * diffuse * shadow ;
	out_Color = vec4(col + diffuse * light, 1.0);
}
