//Taken from glsl.heroku.com
//I am assuming these are public domain and I can use them.
//I have made my best effort to research the origin and license.
//If this is incorrect or you don't want me using them, let me know.

#ifdef GL_ES
precision highp float;
#endif

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

void main( void ) {

       vec2 position = ( gl_FragCoord.xy / resolution.xy ) + time;

       float rand = mod(fract(sin(dot(position, vec2(14.9898,78.233))) * 43758.5453), 1.0);

       gl_FragColor = vec4( rand, rand, rand, 1.0);

}
