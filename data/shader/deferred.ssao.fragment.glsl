#version 130
precision highp float;

const float uNoiseScale = 30.0
const float fov = 60.f;
const int uKernelSize = 10;
const float uRadius = 1.5;
const float uPower = 2.0;

uniform sampler2D  uDepthTexture;  
uniform sampler2D  uNormalTexture;    // Normal rgb depth a
uniform sampler2D  uRandomTexture;    // Random

uniform mat4 uProjectionMatrix;
uniform float uAspect;

smooth in vPosition;
smooth in vec2 vTexCoord;
noperspective in vec3 vViewRay;	

out vec4 outColor;

float linearizeDepth(in float depth, in mat4 projMatrix) {
	return projMatrix[3][2] / (depth - projMatrix[2][2]);
}

float ssao(in mat3 kernelBasis, in vec3 originPos, in float radius) {
	float occlusion = 0.0;
	for (int i = 0; i < uKernelSize; ++i) {
		//get sample position:
		vec3 samplePos = kernelBasis * uKernelOffsets[i];
		samplePos = samplePos * radius + originPos;
		
		//project sample position:
		vec4 offset = uProjectionMatrix * vec4(samplePos, 1.0);
		offset.xy /= offset.w; // only need xy
		offset.xy = offset.xy * 0.5 + 0.5; // scale/bias to texcoords
		
		//get sample depth:
		float sampleDepth = texture(normalTexture, offset.xy).a;
		sampleDepth = linearizeDepth(sampleDepth, uProjectionMatrix);
		
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(originPos.z - sampleDepth));
		occlusion += rangeCheck * step(sampleDepth, samplePos.z);
	}
	
	occlusion = 1.0 - (occlusion / float(uKernelSize));
	return pow(occlusion, uPower);
}

void main() {
	vec3 uKernelOffsets[10] = vec3[](vec3(-0.010735935, 0.01647018, 0.0062425877),vec3(-0.06533369, 0.3647007, -0.13746321),vec3(-0.6539235, -0.016726388, -0.53000957),vec3(0.40958285, 0.0052428036, -0.5591124),vec3(-0.1465366, 0.09899267, 0.15571679),vec3(-0.44122112, -0.5458797, 0.04912532),vec3(0.03755566, -0.10961345, -0.33040273),vec3(0.019100213, 0.29652783, 0.066237666),vec3(0.8765323, 0.011236004, 0.28265962),vec3(0.29264435, -0.40794238, 0.15964167));

	vec2 noiseTexCoords = vec2(textureSize(uDepthTexture, 0)) / vec2(textureSize(uRandomTexture, 0));
	noiseTexCoords *= vTexCoord;

	float originDepth = texture(uDepthTexture, vTexCoord).r;
	originDepth = linearizeDepth(originDepth, uProjectionMatrix);
	vec3 originPos = vViewRay * originDepth;

	//	get view space normal:
	vec3 normal = texture(uNormalTexture, vTexCoord).rgb;

	//	construct kernel basis matrix:
	vec3 rvec = texture(uNoiseTex, noiseTexCoords).rgb * 2.0 - 1.0;
	vec3 tangent = normalize(rvec - normal * dot(rvec, normal));
	vec3 bitangent = cross(tangent, normal);
	mat3 kernelBasis = mat3(tangent, bitangent, normal);


	outColor = vec4(ssao(kernelBasis, originPos, uRadius));
	
}