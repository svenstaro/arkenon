#version 130
precision highp float;

uniform sampler2D position;
uniform sampler2D color;
uniform sampler2D normal;

uniform vec3 lightPosition;
uniform vec3 lightColor;

void main()
{
    vec2 texcoord = gl_FragCoord.xy;
    float distance = distance(texture2D(position, texcoord).xyz, lightPosition);
    vec3 normal =  normalize(texture2D(normal, texcoord).xyz);
    vec3 lightDirection = normalize(texture2D(position, texcoord).xyz - lightPosition);
    vec4 color = vec4(lightColor, 1.0) * 0.8 * dot(normal, -lightDirection);
    float attenuation =  0.0 + 0.008 * distance + 0.002 * distance * distance;
    gl_FragColor = color / attenuation;
}
