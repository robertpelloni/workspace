#pragma once
#ifndef _SDL_stuff_h
#define _SDL_stuff_h
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>



typedef enum
{
	SDL_FALSE = 0,
	SDL_TRUE = 1
} SDL_bool;

/**
* \brief A signed 8-bit integer type.
*/
typedef int8_t Sint8;
/**
* \brief An unsigned 8-bit integer type.
*/
typedef uint8_t Uint8;
/**
* \brief A signed 16-bit integer type.
*/
typedef int16_t Sint16;
/**
* \brief An unsigned 16-bit integer type.
*/
typedef uint16_t Uint16;
/**
* \brief A signed 32-bit integer type.
*/
typedef int32_t Sint32;
/**
* \brief An unsigned 32-bit integer type.
*/
typedef uint32_t Uint32;

/**
* \brief A signed 64-bit integer type.
*/
typedef int64_t Sint64;
/**
* \brief An unsigned 64-bit integer type.
*/
typedef uint64_t Uint64;



/* By default SDL uses the C calling convention */
#ifndef SDLCALL
#if (defined(__WIN32__) || defined(__WINRT__)) && !defined(__GNUC__)
#define SDLCALL __cdecl
#else
#define SDLCALL
#endif
#endif /* SDLCALL */



#define SDL_malloc malloc
#define SDL_calloc calloc
#define SDL_realloc realloc
#define SDL_free free
#define SDL_memset memset
#define SDL_memcpy memcpy
#define SDL_memmove memmove
#define SDL_memcmp memcmp
#define SDL_strlen strlen
#define SDL_strlcpy strlcpy
#define SDL_strlcat strlcat
#define SDL_strdup strdup
#define SDL_strchr strchr
#define SDL_strrchr strrchr
#define SDL_strstr strstr
#define SDL_strcmp strcmp
#define SDL_strncmp strncmp
#define SDL_strcasecmp strcasecmp
#define SDL_strncasecmp strncasecmp
#define SDL_sscanf sscanf
#define SDL_vsscanf vsscanf
#define SDL_snprintf snprintf
#define SDL_vsnprintf vsnprintf

//#define SDL_memset memset
//#define SDL_memcpy memcpy
//#define SDL_memcmp memcmp
//#define SDL_memmove memmove
//#define SDL_malloc malloc
//#define SDL_calloc calloc
//#define SDL_realloc realloc
//#define SDL_free free
//#define SDL_strlen strlen
#define SDL_stack_alloc(type, count)    (type*)SDL_malloc(sizeof(type)*(count))
#define SDL_stack_free free
//#define SDL_strchr strchr
//#define SDL_strlcpy strlcpy


#define SDL_SetError printf

#define SDL_ceil ceil
#define SDL_floor floor
#define SDL_pow pow




typedef enum
{
	SDL_ENOMEM,
	SDL_EFREAD,
	SDL_EFWRITE,
	SDL_EFSEEK,
	SDL_UNSUPPORTED,
	SDL_LASTERROR
} SDL_errorcode;


/* Very common errors go here */
inline int
SDL_Error(SDL_errorcode code)
{
	switch (code)
	{
	case SDL_ENOMEM:
		return SDL_SetError("Out of memory");
	case SDL_EFREAD:
		return SDL_SetError("Error reading from datastream");
	case SDL_EFWRITE:
		return SDL_SetError("Error writing to datastream");
	case SDL_EFSEEK:
		return SDL_SetError("Error seeking in datastream");
	case SDL_UNSUPPORTED:
		return SDL_SetError("That operation is not supported");
	default:
		return SDL_SetError("Unknown SDL error");
	}
}

#define SDL_OutOfMemory()   SDL_Error(SDL_ENOMEM)
#define SDL_Unsupported()   SDL_Error(SDL_UNSUPPORTED)
#define SDL_InvalidParamError(param)    SDL_SetError("Parameter '%s' is invalid", (param))










/**
*  \name Cast operators
*
*  Use proper C++ casts when compiled as C++ to be compatible with the option
*  -Wold-style-cast of GCC (and -Werror=old-style-cast in GCC 4.2 and above).
*/
/* @{ */
#ifdef __cplusplus
#define SDL_reinterpret_cast(type, expression) reinterpret_cast<type>(expression)
#define SDL_static_cast(type, expression) static_cast<type>(expression)
#define SDL_const_cast(type, expression) const_cast<type>(expression)
#else
#define SDL_reinterpret_cast(type, expression) ((type)(expression))
#define SDL_static_cast(type, expression) ((type)(expression))
#define SDL_const_cast(type, expression) ((type)(expression))
#endif
/* @} *//* Cast operators */




#ifndef SDL_INLINE
#if defined(__GNUC__)
#define SDL_INLINE __inline__
#elif defined(_MSC_VER) || defined(__BORLANDC__) || \
      defined(__DMC__) || defined(__SC__) || \
      defined(__WATCOMC__) || defined(__LCC__) || \
      defined(__DECC)
#define SDL_INLINE __inline
#ifndef __inline__
#define __inline__ __inline
#endif
#else
#define SDL_INLINE inline
#ifndef __inline__
#define __inline__ inline
#endif
#endif
#endif /* SDL_INLINE not defined */

#ifndef SDL_FORCE_INLINE
#if defined(_MSC_VER)
#define SDL_FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#define SDL_FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#define SDL_FORCE_INLINE static SDL_INLINE
#endif
#endif /* SDL_FORCE_INLINE not defined */


#define SDL_LIL_ENDIAN 1
#define SDL_BIG_ENDIAN 2

#define SDL_BYTEORDER   SDL_LIL_ENDIAN



///**
//*  \file SDL_endian.h
//*/
//#if defined(__GNUC__) && defined(__i386__) && \
//   !(__GNUC__ == 2 && __GNUC_MINOR__ == 95 /* broken gcc version */)
//SDL_FORCE_INLINE Uint16
//SDL_Swap16(Uint16 x)
//{
//	__asm__("xchgb %b0,%h0": "=q"(x) : "0"(x));
//	return x;
//}
//#elif defined(__GNUC__) && defined(__x86_64__)
//SDL_FORCE_INLINE Uint16
//SDL_Swap16(Uint16 x)
//{
//	__asm__("xchgb %b0,%h0": "=Q"(x) : "0"(x));
//	return x;
//}
//#elif defined(__GNUC__) && (defined(__powerpc__) || defined(__ppc__))
//SDL_FORCE_INLINE Uint16
//SDL_Swap16(Uint16 x)
//{
//	int result;
//
//	__asm__("rlwimi %0,%2,8,16,23": "=&r"(result) : "0"(x >> 8), "r"(x));
//	return (Uint16)result;
//}
//#elif defined(__GNUC__) && (defined(__M68000__) || defined(__M68020__)) && !defined(__mcoldfire__)
//SDL_FORCE_INLINE Uint16
//SDL_Swap16(Uint16 x)
//{
//	__asm__("rorw #8,%0": "=d"(x) : "0"(x) : "cc");
//	return x;
//}
//#else
SDL_FORCE_INLINE Uint16
SDL_Swap16(Uint16 x)
{
	return SDL_static_cast(Uint16, ((x << 8) | (x >> 8)));
}
//#endif

//#if defined(__GNUC__) && defined(__i386__)
//SDL_FORCE_INLINE Uint32
//SDL_Swap32(Uint32 x)
//{
//	__asm__("bswap %0": "=r"(x) : "0"(x));
//	return x;
//}
//#elif defined(__GNUC__) && defined(__x86_64__)
//SDL_FORCE_INLINE Uint32
//SDL_Swap32(Uint32 x)
//{
//	__asm__("bswapl %0": "=r"(x) : "0"(x));
//	return x;
//}
//#elif defined(__GNUC__) && (defined(__powerpc__) || defined(__ppc__))
//SDL_FORCE_INLINE Uint32
//SDL_Swap32(Uint32 x)
//{
//	Uint32 result;
//
//	__asm__("rlwimi %0,%2,24,16,23": "=&r"(result) : "0"(x >> 24), "r"(x));
//	__asm__("rlwimi %0,%2,8,8,15": "=&r"(result) : "0"(result), "r"(x));
//	__asm__("rlwimi %0,%2,24,0,7": "=&r"(result) : "0"(result), "r"(x));
//	return result;
//}
//#elif defined(__GNUC__) && (defined(__M68000__) || defined(__M68020__)) && !defined(__mcoldfire__)
//SDL_FORCE_INLINE Uint32
//SDL_Swap32(Uint32 x)
//{
//	__asm__("rorw #8,%0\n\tswap %0\n\trorw #8,%0": "=d"(x) : "0"(x) : "cc");
//	return x;
//}
//#else
SDL_FORCE_INLINE Uint32
SDL_Swap32(Uint32 x)
{
	return SDL_static_cast(Uint32, ((x << 24) | ((x << 8) & 0x00FF0000) |
		((x >> 8) & 0x0000FF00) | (x >> 24)));
}
//#endif

//#if defined(__GNUC__) && defined(__i386__)
//SDL_FORCE_INLINE Uint64
//SDL_Swap64(Uint64 x)
//{
//	union
//	{
//		struct
//		{
//			Uint32 a, b;
//		} s;
//		Uint64 u;
//	} v;
//	v.u = x;
//	__asm__("bswapl %0 ; bswapl %1 ; xchgl %0,%1": "=r"(v.s.a), "=r"(v.s.b) : "0"(v.s.a),
//		"1"(v.s.
//			b));
//	return v.u;
//}
//#elif defined(__GNUC__) && defined(__x86_64__)
//SDL_FORCE_INLINE Uint64
//SDL_Swap64(Uint64 x)
//{
//	__asm__("bswapq %0": "=r"(x) : "0"(x));
//	return x;
//}
//#else
SDL_FORCE_INLINE Uint64
SDL_Swap64(Uint64 x)
{
	Uint32 hi, lo;

	/* Separate into high and low 32-bit values and swap them */
	lo = SDL_static_cast(Uint32, x & 0xFFFFFFFF);
	x >>= 32;
	hi = SDL_static_cast(Uint32, x & 0xFFFFFFFF);
	x = SDL_Swap32(lo);
	x <<= 32;
	x |= SDL_Swap32(hi);
	return (x);
}
//#endif


SDL_FORCE_INLINE float
SDL_SwapFloat(float x)
{
	union
	{
		float f;
		Uint32 ui32;
	} swapper;
	swapper.f = x;
	swapper.ui32 = SDL_Swap32(swapper.ui32);
	return swapper.f;
}


/**
*  \name Swap to native
*  Byteswap item from the specified endianness to the native endianness.
*/
/* @{ */
#if SDL_BYTEORDER == SDL_LIL_ENDIAN
#define SDL_SwapLE16(X) (X)
#define SDL_SwapLE32(X) (X)
#define SDL_SwapLE64(X) (X)
#define SDL_SwapFloatLE(X)  (X)
#define SDL_SwapBE16(X) SDL_Swap16(X)
#define SDL_SwapBE32(X) SDL_Swap32(X)
#define SDL_SwapBE64(X) SDL_Swap64(X)
#define SDL_SwapFloatBE(X)  SDL_SwapFloat(X)
#else
#define SDL_SwapLE16(X) SDL_Swap16(X)
#define SDL_SwapLE32(X) SDL_Swap32(X)
#define SDL_SwapLE64(X) SDL_Swap64(X)
#define SDL_SwapFloatLE(X)  SDL_SwapFloat(X)
#define SDL_SwapBE16(X) (X)
#define SDL_SwapBE32(X) (X)
#define SDL_SwapBE64(X) (X)
#define SDL_SwapFloatBE(X)  (X)
#endif


//
//typedef struct SDL_Color
//{
//	Uint8 r;
//	Uint8 g;
//	Uint8 b;
//	Uint8 a;
//} SDL_Color;
//#define SDL_Colour SDL_Color
//
//typedef struct SDL_Palette
//{
//	int ncolors;
//	SDL_Color *colors;
//	Uint32 version;
//	int refcount;
//} SDL_Palette;
///**
//*  \note Everything in the pixel format structure is read-only.
//*/
//typedef struct SDL_PixelFormat
//{
//	Uint32 format;
//	SDL_Palette *palette;
//	Uint8 BitsPerPixel;
//	Uint8 BytesPerPixel;
//	Uint8 padding[2];
//	Uint32 Rmask;
//	Uint32 Gmask;
//	Uint32 Bmask;
//	Uint32 Amask;
//	Uint8 Rloss;
//	Uint8 Gloss;
//	Uint8 Bloss;
//	Uint8 Aloss;
//	Uint8 Rshift;
//	Uint8 Gshift;
//	Uint8 Bshift;
//	Uint8 Ashift;
//	int refcount;
//	struct SDL_PixelFormat *next;
//} SDL_PixelFormat;
//

///**
//*  \brief A rectangle, with the origin at the upper left.
//*
//*  \sa SDL_RectEmpty
//*  \sa SDL_RectEquals
//*  \sa SDL_HasIntersection
//*  \sa SDL_IntersectRect
//*  \sa SDL_UnionRect
//*  \sa SDL_EnclosePoints
//*/
//typedef struct SDL_Rect
//{
//	int x, y;
//	int w, h;
//} SDL_Rect;
//
///**
//* \brief A collection of pixels used in software blitting.
//*
//* \note  This structure should be treated as read-only, except for \c pixels,
//*        which, if not NULL, contains the raw pixel data for the surface.
//*/
//typedef struct SDL_Surface
//{
//	Uint32 flags;               /**< Read-only */
//	SDL_PixelFormat *format;    /**< Read-only */
//	int w, h;                   /**< Read-only */
//	int pitch;                  /**< Read-only */
//	void *pixels;               /**< Read-write */
//
//								/** Application data associated with the surface */
//	void *userdata;             /**< Read-write */
//
//								/** information needed for surfaces requiring locks */
//	int locked;                 /**< Read-only */
//	void *lock_data;            /**< Read-only */
//
//								/** clipping information */
//	SDL_Rect clip_rect;         /**< Read-only */
//
//								/** info for fast blit mapping to other surfaces */
//	struct SDL_BlitMap *map;    /**< Private */
//
//								/** Reference count -- used when freeing surface */
//	int refcount;               /**< Read-mostly */
//} SDL_Surface;
//
//
//


/* Note that memset() is a byte assignment and this is a 32-bit assignment, so they're not directly equivalent. */
SDL_FORCE_INLINE void SDL_memset4(void *dst, Uint32 val, size_t dwords)
{
//#if defined(__GNUC__) && defined(i386)
//	int u0, u1, u2;
//	__asm__ __volatile__(
//		"cld \n\t"
//		"rep ; stosl \n\t"
//		: "=&D" (u0), "=&a" (u1), "=&c" (u2)
//		: "0" (dst), "1" (val), "2" (SDL_static_cast(Uint32, dwords))
//		: "memory"
//	);
//#else
	size_t _n = (dwords + 3) / 4;
	Uint32 *_p = SDL_static_cast(Uint32 *, dst);
	Uint32 _val = (val);
	if (dwords == 0)
		return;
	switch (dwords % 4)
	{
	case 0: do
	{
		*_p++ = _val;
	case 3:         *_p++ = _val;
	case 2:         *_p++ = _val;
	case 1:         *_p++ = _val;
	} while (--_n);
	}
//#endif
}

#define SDL_zero(x) SDL_memset(&(x), 0, sizeof((x)))
#define SDL_zerop(x) SDL_memset((x), 0, sizeof(*(x)))


/**
*  \brief The blend mode used in SDL_RenderCopy() and drawing operations.
*/
typedef enum
{
	SDL_BLENDMODE_NONE = 0x00000000,     /**< no blending
										 dstRGBA = srcRGBA */
	SDL_BLENDMODE_BLEND = 0x00000001,    /**< alpha blending
										 dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
										 dstA = srcA + (dstA * (1-srcA)) */
	SDL_BLENDMODE_ADD = 0x00000002,      /**< additive blending
										 dstRGB = (srcRGB * srcA) + dstRGB
										 dstA = dstA */
	SDL_BLENDMODE_MOD = 0x00000004       /**< color modulate
										 dstRGB = srcRGB * dstRGB
										 dstA = dstA */
} SDL_BlendMode;


/* Define a four character code as a Uint32 */
#define SDL_FOURCC(A, B, C, D) \
    ((SDL_static_cast(Uint32, SDL_static_cast(Uint8, (A))) << 0) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (B))) << 8) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (C))) << 16) | \
     (SDL_static_cast(Uint32, SDL_static_cast(Uint8, (D))) << 24))


#endif