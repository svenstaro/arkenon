#version 130
precision highp float;

uniform sampler2D colorMap;
uniform sampler2D positionMap;
uniform sampler2D normalMap;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float lightRadius;
uniform vec2 screenSize;

uniform mat4 VP;
uniform mat4 M;

void main()
{
    vec2 texcoord = gl_FragCoord.xy / screenSize;
    vec3 position = texture2D(positionMap, texcoord).xyz;
    vec3 normal = texture2D(normalMap, texcoord).xyz;
    vec3 color = texture2D(colorMap, texcoord).rgb;

//    normal = normalize(normal);
//    vec3 lightDirection = normalize(lightPosition - position);

//    vec3 cameraPosition = (VP * vec4(0, 0, 0, 1)).xyz;
//    vec3 eyeDir = normalize(cameraPosition - position);
//    vec3 vHalfVector = normalize(lightDirection+eyeDir);

//    gl_FragColor = vec4(dot(normal, -lightDirection) * color, 1.f);
//                   max(dot(normal,lightDirection),0) * color +
//                   pow(max(dot(normal,vHalfVector),0.0), 2) * 1.5,
//                1.f);




    float distance = distance(position, lightPosition);
    normal = normalize(normal);
    vec3 lightDirection = normalize(position - lightPosition);

    float diffuse_factor = dot(normal, -lightDirection);
    vec3 light = lightColor.rgb * lightColor.a * diffuse_factor;

    // TODO: specularity here

    float alpha = distance / lightRadius;
    float beta = .25;
    float damping_factor = 1.0 - pow(alpha, beta);
    float intensity = (1-alpha) * damping_factor;

    vec3 result = light * color;

    float attenuation = 1;//0.00 + 0.02 * distance + 0.008 * distance * distance;

    gl_FragColor = vec4(result / attenuation, 1);
}