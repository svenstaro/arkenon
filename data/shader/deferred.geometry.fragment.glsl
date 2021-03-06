#version 130
precision highp float;

in vec3 var_position;
in vec2 var_textureCoords;
in vec4 var_color;
in vec3 var_normal;
in vec3 var_tangent;
in vec3 var_bitangent;

out vec4 color;
out vec3 position;
out vec3 normal;
out vec3 specular;

uniform sampler2D diffuseTexture;
uniform vec4 diffuseColor;
uniform sampler2D normalTexture;
uniform sampler2D specularTexture;
uniform float specularShininess;
uniform float specularColorMix;
uniform bool hasNormalTexture;

float toGrayscale(vec3 color) {
    return (color.r + color.g + color.b) / 3.f;
}

void main()
{
    color = vec4(texture(diffuseTexture, var_textureCoords).rgb * diffuseColor.rgb, 0);
	position = var_position; 

	if(hasNormalTexture) {

    	vec3 ts_normal = texture(normalTexture, var_textureCoords).xyz * 2.0 - vec3(1.0);
    	vec3 ws_normal =
            (var_tangent) * ts_normal.x +
            (var_bitangent) * ts_normal.y +
            (var_normal) * ts_normal.z;

    	normal = ws_normal;
    } else {
    	normal = var_normal;
    }

    float specularIntensity = toGrayscale(texture(specularTexture, var_textureCoords).rgb);
    specular = vec3(specularIntensity, specularShininess, specularColorMix);

 }
