#version 130
precision highp float;

uniform sampler2D  depthTexture;    // Depth in linear format
uniform sampler2D  normalTexture;    // Normal
uniform sampler2D  randomTexture;    // Random

in vec2 out_TextureCoords;

out vec4 out_Color;

const float strength = 0.09;
const float offsetAO = 30.0;
const float falloff = 0.00001;
const float rad = 0.01;

void main() {

	float depthScreen = texture2D(depthTexture, out_TextureCoords).x;

	if (depthScreen==1.0) {  
		 out_Color = vec4(1.0,1.0,1.0,1.0);
	} else {

		vec3 normal = texture2D(normalTexture, out_TextureCoords).xyz*2.0 -1.0;

		vec3 pSphere[10] = vec3[](vec3(-0.010735935, 0.01647018, 0.0062425877),vec3(-0.06533369, 0.3647007, -0.13746321),vec3(-0.6539235, -0.016726388, -0.53000957),vec3(0.40958285, 0.0052428036, -0.5591124),vec3(-0.1465366, 0.09899267, 0.15571679),vec3(-0.44122112, -0.5458797, 0.04912532),vec3(0.03755566, -0.10961345, -0.33040273),vec3(0.019100213, 0.29652783, 0.066237666),vec3(0.8765323, 0.011236004, 0.28265962),vec3(0.29264435, -0.40794238, 0.15964167));

		vec3 fres = normalize(texture2D(randomTexture, out_TextureCoords * offsetAO).xyz);
		float occluderDepth, depthDifference;
		vec4 occluderNormal;
		vec3 ray;
		vec2 uv_Sample;
		float radD = rad * depthScreen;

		float bl = 0.0;
		for(int i=0; i<10;++i) {
	    	// get a vector (randomized inside of a sphere with radius 1.0) from a texture and reflect it
			ray =radD * reflect(pSphere[i],fres);
	 
			uv_Sample = out_TextureCoords + (sign(dot(ray, normal.xyz) )) * ray.xy;
			occluderDepth = texture2D(depthTexture, uv_Sample).r;
			occluderNormal = texture2D(normalTexture,uv_Sample);
			depthDifference = depthScreen-occluderDepth;
	 
			bl += step(falloff, depthDifference) * (1.0 - dot(occluderNormal.xyz, normal)) * (1.0 - smoothstep(falloff, strength, depthDifference));
		}

		float result = 1 * clamp(1 - (bl / 10.0), 0.0, 1.0);

		out_Color = vec4(result, result, result, 1.0);
	}
}