#pragma once


float simplexnoise_noise1( float x );
float simplexnoise_noise2( float x, float y );
float simplexnoise_noise3( float x, float y, float z );
float simplexnoise_noise4( float x, float y, float z, float w );

float simplexnoise_pnoise1( float x, int px );
float simplexnoise_pnoise2( float x, float y, int px, int py );
float simplexnoise_pnoise3( float x, float y, float z, int px, int py, int pz );
float simplexnoise_pnoise4( float x, float y, float z, float w,
                          int px, int py, int pz, int pw );

float  simplexnoise_grad1( int hash, float x );
float  simplexnoise_grad2( int hash, float x, float y );
float  simplexnoise_grad3( int hash, float x, float y , float z );
float  simplexnoise_grad4( int hash, float x, float y, float z, float t );
