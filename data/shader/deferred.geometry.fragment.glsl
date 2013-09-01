#version 130
precision highp float;

in vec4 out_Color;
in vec3 out_Position;
in vec3 out_Normal;
in vec2 out_TextureCoords;

out vec3 color;
out vec3 position;
out vec3 normal;

uniform sampler2D diffuseTexture;
uniform vec4 diffuseColor;
uniform sampler2D normalTexture;

void main()
{
    // DIFFUSE: multiply blending, diffuse texture with diffuse color
    color = texture(diffuseTexture, out_TextureCoords).rgb * diffuseColor.rgb;

    // POSITION
    position = out_Position;

    // NORMAL
    vec3 textureNormal = texture2D(normalTexture, out_TextureCoords).xyz;
    normal = normalize(out_Normal + textureNormal);
}
