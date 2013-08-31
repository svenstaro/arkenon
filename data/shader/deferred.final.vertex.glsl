#version 130
precision highp float;

in vec3 in_Position;
in vec2 in_TextureCoords;

uniform mat4 projMatrix;

out vec2 out_TextureCoords;

void main(){
	gl_Position = projMatrix * vec4(in_Position , 1.0);
	out_TextureCoords = in_TextureCoords;
}