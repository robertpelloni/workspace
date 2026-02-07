//Taken from glsl.heroku.com
//I am assuming these are public domain and I can use them.
//I have made my best effort to research the origin and license.
//If this is incorrect or you don't want me using them, let me know.

#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

//Matrix

void main( void ) {	
	gl_FragColor = vec4( 0, -mod(gl_FragCoord.y +time , cos(gl_FragCoord.x)+0.004)*.5, 0 ,1);
}