#version 130
precision highp float;

uniform sampler2D colorMap;
uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform float lightRadius;
uniform vec2 screenSize;

uniform vec3 cameraPosition;

out vec4 out_colorMultiply;
out vec4 out_colorAdd;

void main()
{
    vec2 texcoord = gl_FragCoord.xy / screenSize;
    vec3 position = texture(positionMap, texcoord).xyz;
    vec3 normal = texture(normalMap, texcoord).xyz;
    vec3 specularData = texture(specularMap, texcoord).xyz; // intensity, shininess, colormix

    float distance = distance(position, lightPosition);
    //normal = normalize(normal);
    vec3 lightDirection = normalize(position - lightPosition);

    float diffuse_factor = dot(normal, -lightDirection);
    vec3 light = lightColor.rgb * lightColor.a * diffuse_factor;

    // TODO: specularity here

    float alpha = distance / lightRadius;
    float beta = 2;
    float damping_factor = 1.0 - pow(alpha, beta);
    float intensity = clamp(1-alpha, 0, 1) * damping_factor;

    vec3 result = light * 1 * intensity;
    out_colorMultiply = vec4(result, 1);

    // specular
    vec3 surfaceToCamera = normalize(cameraPosition - position);
    //vec3 reflectionVector = reflect(lightDirection, normal);
    //float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    vec3 halfway = normalize(-lightDirection + surfaceToCamera);
    float cosAngle = max(0.0, dot(halfway, normal));
    float specularCoefficient = pow(cosAngle, specularData.y);
    vec3 specularColor = mix(lightColor.rgb, vec3(1, 1, 1), specularData.z);
    vec3 specularComponent = specularCoefficient * specularColor * specularData.x * intensity;

    // attenuation
    //float attenuation = 1.0 / (1.0 + light.attenuation * pow(distanceToLight, 2));
    out_colorAdd = vec4(specularComponent.rgb, 0);
}
