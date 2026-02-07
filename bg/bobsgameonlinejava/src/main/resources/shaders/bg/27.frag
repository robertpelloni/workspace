//Taken from glsl.heroku.com
//I am assuming these are public domain and I can use them.
//I have made my best effort to research the origin and license.
//If this is incorrect or you don't want me using them, let me know.

// Some hills...

#ifdef GL_ES
precision highp float;
#endif

uniform vec2 resolution; 
uniform float time;
uniform vec2 mouse;
//Simple raymarching sandbox with camera

//Raymarching Distance Fields
//About http://www.iquilezles.org/www/articles/raymarchingdf/raymarchingdf.htm
//Also known as Sphere Tracing
//Original seen here: http://twitter.com/#!/paulofalcao/statuses/134807547860353024

//Util Start

mat2 m = mat2( 0.80,  0.60, -0.60,  0.80 );

float hash( float n )
{
    return fract(sin(n)*43758.5453);
}

float noise( in vec2 x )
{
    vec2 p = floor(x);
    vec2 f = fract(x);
    f = f*f*(3.0-2.0*f);
    float n = p.x + p.y*57.0;
    float res = mix(mix( hash(n+  0.0), hash(n+  1.0),f.x), mix( hash(n+ 57.0), hash(n+ 58.0),f.x),f.y);
    return res;
}

float fbm( vec2 p )
{
    float f = 0.0;
    float t1 = time * .1;
    f += 0.50000*noise( p + t1 * 4.0); p = m*p*2.02;
    f += 0.25000*noise( p + t1 * 5.0 ); p = m*p*2.03;
    f += 0.12500*noise( p + t1 * 6.0 ); p = m*p*2.01;
    f += 0.06250*noise( p + t1 * 7.0 ); p = m*p*2.04;
    f += 0.03125*noise( p + t1 * 8.0 );
    return f/0.984375;
}
vec2 ObjUnion(in vec2 obj_floor,in vec2 obj_roundBox){
  if (obj_floor.x<obj_roundBox.x)
  	return obj_floor;
  else
  	return obj_roundBox;
}
//Util End

//Scene Start

//Torus
float torus(in vec3 p, in vec2 t){
	vec2 q = vec2(length(vec2(p.x,p.z))-t.x, p.y);
	return length(q) - t.y;
}

//Sphere
float sphere(in vec3 p, float radius){
	float length = sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
	return length-radius;
}

//Floor
vec2 obj_floor(in vec3 p){
  return vec2(p.y+fbm(p.xz / 12.0) * 13.0,0);
}
//Floor Color (checkerboard)
vec3 obj_floor_c(in vec3 p){
 return vec3(0.5, 0.5, 0.5); //, vec3(0.0, 0.1, 0.9), fbm(p.xz * 0.2)) * 5.6 + fbm(p.xz * 8.0 + fbm(p.zx * 2.0)) * 0.4;
}

//IQs RoundBox (try other objects http://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm)
vec2 obj_roundBox(in vec3 p){
  return vec2(length(max(abs(p)-vec3(1,1,1),0.0))-0.25,1);
}

vec2 obj_sphere(in vec3 p){
  return vec2(length(p)-2.0);
}

//RoundBox with simple solid color
vec3 obj_roundBox_c(in vec3 p){
	return vec3(1.0,0.5,0.2);
}

//Objects union
vec2 inObj(in vec3 p){
  return obj_floor(p);
}

//Scene End

void main(void){
  //Camera animation
  vec3 U=vec3(0,1,0);//Camera Up Vector

  vec3 E=vec3(time*5.0, 3, 0);//vec3(-sin(time/4.0)*8.0,4,cos(time/4.0)*8.0); //Camera location; Change camera path position here
  vec3 viewDir=vec3(E.x-sin(mouse.x*5.0),1.0+mouse.y*2.0,E.z+cos(mouse.x*5.0)); //Change camere view vector here
  //vec3 E=vec3(mouse.x*4.0, 4, mouse.y*4.0); //Camera location; Change camera path position here
	
  //Camera setup
  vec3 C=normalize(viewDir-E);
  vec3 A=cross(C, U);
  vec3 B=cross(A, C);
  vec3 M=(E+C);
  
  vec2 vPos=2.0*gl_FragCoord.xy/resolution.xy - 1.0; // (2*Sx-1) where Sx = x in screen space (between 0 and 1)
  vec3 scrCoord=M + vPos.x*A*resolution.x/resolution.y + vPos.y*B; //normalize resolution in either x or y direction (ie resolution.x/resolution.y)
  vec3 scp=normalize(scrCoord-E);

  //Raymarching
  const vec3 e=vec3(0.1,0,0);
  const float MAX_DEPTH=60.0; //Max depth

  vec2 s=vec2(0.1,0.0);
  vec3 c,p,n;

  float f=1.0;
  for(int i=0;i<256;i++){
    if (abs(s.x)<.01||f>MAX_DEPTH) break;
    f+=s.x;
    p=E+scp*f;
    s=inObj(p);
  }
  
  if (f<MAX_DEPTH){
    if (s.y==0.0)
      c=obj_floor_c(p);
    else
      c=obj_roundBox_c(p);
    n=normalize(
      vec3(s.x-inObj(p-e.xyy).x,
           s.x-inObj(p-e.yxy).x,
           s.x-inObj(p-e.yyx).x));
    float b=dot(n,normalize(E-p));
    float s=clamp(pow(b,25.0),0.0,1.0);
    gl_FragColor=vec4(b*c*(1.0-f*.01),1.0)+vec4(vec3(s),1.0);//simple phong LightPosition=CameraPosition
	
  }
  else gl_FragColor=vec4(0,0,0,1); //background color
}