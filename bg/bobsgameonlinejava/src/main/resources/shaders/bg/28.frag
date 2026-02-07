//Taken from glsl.heroku.com
//I am assuming these are public domain and I can use them.
//I have made my best effort to research the origin and license.
//If this is incorrect or you don't want me using them, let me know.

#ifdef GL_ES
precision mediump float;
#endif
 
#define PI 3.14159
 
#define RECT(l,s,p) float(p.x >= l.x && p.x <= l.x+s.x && p.y >= l.y && p.y <= l.y+s.y )
 
uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;
uniform sampler2D backbuffer;

float t = time/10.0;
 
float round(float v)
{
	if(fract(v) >= 0.5){ return ceil(v); }
	return floor(v);
}
 
float rand(vec2 co){	
    return fract(sin(dot(co.xy,vec2(12.9898,78.233))) * 43758.5453);
}
 
vec3 pattern(vec2 p,vec2 r,float ch)
{
	vec2 pos = mod(p,r);
	
	float c = 0.0;
	
	if(ch == 0.0)
	{
		c += RECT(vec2(3,2),vec2(8.,12.),pos);
		c -= RECT(vec2(5.,4.),vec2(4.,8.),pos);
	}
	if(ch == 1.0)
	{
		c += RECT(vec2(6.,2.),vec2(2.,12.),pos);
		c += RECT(vec2(4.,12.),vec2(2.,2.),pos);
		c += RECT(vec2(3.,2.),vec2(8.,2.),pos);
	}
	c = clamp(c,0.0,1.0);
	
	float b = (rand(vec2(round((p.x)/16.0+0.5))+t))*0.75+0.25;
	
	return vec3(0,c*b,0);
}
 
 
 
void main( void ) {
 
	
	vec3 color = vec3(0.0);
	vec2 p = ( gl_FragCoord.xy);
	if (gl_FragCoord.y == 0.5)
	{
		if (gl_FragCoord.x == 0.5)
		{
			float t = texture2D(backbuffer,vec2(0.0,0.0)).g + 0.15;
			if (t >= 1.0)
				t = 0.0;
			color.g = t;
		}
		else
			color.g = rand(vec2(gl_FragCoord.x, t));
	}
	else
	{
		vec2 rpos = vec2( round(p.x/16.+0.5), round(p.y/16.+0.5));
		float rch = mod(rpos.x,2.0);
		rch = round(rand(vec2(rpos+t)));
		
		float t = texture2D(backbuffer,vec2(0.0,0.0)).g;
		if(p.y < 16. && t == 0.0)
		{
			color = pattern(p-vec2(0.0,16.0*t),vec2(16.),rch);
		}
		else if (p.y > 3.0)
			color += texture2D(backbuffer,(p-vec2(0.0,2.0))/resolution).rgb-0.002;
	}
	gl_FragColor = vec4( color, 1.0 );
}
