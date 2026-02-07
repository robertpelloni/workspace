//Taken from glsl.heroku.com
//I am assuming these are public domain and I can use them.
//I have made my best effort to research the origin and license.
//If this is incorrect or you don't want me using them, let me know.

#ifdef GL_ES
precision mediump float;
#endif

// Posted by Trisomie21

uniform float time;
uniform vec2 resolution;

// from http://glsl.heroku.com/e#5248.0
#define BLADES 6.0
#define BIAS 0.1
#define SHARPNESS 3.0


// Tweaked from http://glsl.heroku.com/e#4982.0
float hash( float n ) { return fract(sin(n)*43758.5453); }

float noise( in vec2 x )
{
	vec2 p = floor(x);
	vec2 f = fract(x);
    	f = f*f*(3.0-2.0*f);
    	float n = p.x + p.y*57.0;
    	float res = mix(mix(hash(n+0.0), hash(n+1.0),f.x), mix(hash(n+57.0), hash(n+58.0),f.x),f.y);
    	return res;
}

vec3 cloud(vec2 p) {
	float f = 0.0;
    	f += 0.50000*noise(p*1.0*10.0); 
    	f += 0.25000*noise(p*2.0*10.0); 
    	f += 0.12500*noise(p*4.0*10.0); 
    	f += 0.06250*noise(p*8.0*10.0);	
	f *= f;
	return vec3(f*.65, f*.45, f)*.6;
}

const float LAYERS	= 4.0;
const float SPEED	= 0.005;
const float SCALE	= 80.0;
const float DENSITY	= 1.5;
const float BRIGHTNESS	= 10.0;
       vec2 ORIGIN	= resolution.xy*.5;

float rand(vec2 co){ return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453); }

void main( void ) {
	
	vec2   pos = gl_FragCoord.xy - ORIGIN;
	float dist = length(pos) / resolution.y;
	vec2 coord = vec2(pow(dist, 0.1), atan(pos.x, pos.y) / (3.1415926*2.0));
	
	// Nebulous cloud
	vec3 color = cloud(pos/resolution);
	
	// Background stars
	float a = pow((1.0-dist),20.0);
	float t = time*-.05;
	float r = coord.x - (t*SPEED);
	float c = fract(a+coord.y + 0.0*.543);
	vec2  p = vec2(r, c*.5)*4000.0;
	vec2 uv = fract(p)*2.0-1.0;
	float m = clamp((rand(floor(p))-.9)*BRIGHTNESS, 0.0, 1.0);
	color +=  clamp((1.0-length(uv*2.0))*m*dist, 0.0, 1.0);
	
	
	

	
	gl_FragColor = vec4(color, 1.0);
}