#version 130
in vec2 out_TextureCoords;
in vec4 out_Color;
in vec3 out_Normal;

out vec4 color;

uniform vec2 size;
uniform mat4 VP;

#define iterations 18
#define formuparam 0.56

#define volsteps 1
#define stepsize 0.2500

#define zoom   1
#define tile   1
#define speed  0.010

#define brightness 0.0015
#define darkmatter 0.300
#define distfading 0.860
#define saturation 0.800

void main(void)
{
    //get coords and direction
    vec2 uv=out_TextureCoords;
    uv.y *= 0.7;

    //mouse rotation
    vec3 from=vec3(1, 0.5,0.5);
    vec3 dir=vec3(uv*zoom,1.);

    //volumetric rendering
    float s=0.1,fade=1.;
    vec3 v=vec3(0.);
    for (int r=0; r<volsteps; r++) {
        vec3 p=from+s*dir*.5;
        p = abs(vec3(tile)-mod(p,vec3(tile))); // tiling fold
        float pa,a=pa=0.;
        for (int i=0; i<iterations; i++) {
            p=abs(p)/dot(p,p)-formuparam; // the magic formula
            a+=abs(length(p)-pa); // absolute sum of average change
            pa=length(p);
        }
        float dm=max(0.,darkmatter-a*a*.001); //dark matter
        a*=a*a; // add contrast
        if (r>3) fade*=1.-dm; // dark matter, don't render near
        v+=vec3(dm,dm*.5,0.);
        v+=fade;
        v+=vec3(s,s*s,s*s*s*s)*a*brightness*fade; // coloring based on distance
        fade*=distfading; // distance fading
        s+=stepsize;
    }
    v=mix(vec3(length(v)),v,saturation); //color adjust
    color = vec4(v*.01,1.);
}
