#pragma once
#ifndef bobtypes_h
#define bobtypes_h




#ifndef ORBIS

//#define _USING_V110_SDK71_ 1

//#ifdef _MSC_VER
//#define _CRT_SECURE_NO_WARNINGS 1
//#endif
#define _CRT_SECURE_NO_WARNINGS 1

#include "SDL_platform.h"
#endif

#ifdef __WINDOWS__
#include "vcruntime.h"
#endif

//#define GOOGLE_ARRAYSIZE(a) ((sizeof(a) / sizeof(*(a))) / static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

///-----------------------------
///C libs
///-----------------------------
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <string.h>
//
//#include <stdarg.h>
//#include <assert.h>
//#include <setjmp.h>
//#include <sys/stat.h>
//#include <errno.h>
//#include <fcntl.h>
//#include <malloc.h>



///-----------------------------
///C++ libs
///-----------------------------
//#include <iostream>
//#include <iomanip>
#include <string>

#include <vector>
//#include <deque>
//#include <algorithm>
//#include <unordered_map>
//#include <utility>
//#include <limits>
//#include <random>
//#include <fstream>
#include <memory>
//#include <cmath>

template<typename T> using sp = std::shared_ptr<T>;
template<typename T, typename... Args> inline sp<T> ms(Args&&... args) { return std::make_shared<T>(std::forward<Args>(args)...); }

typedef signed char			int8;
typedef signed short		int16;
typedef signed int			int32;
typedef signed long long	int64;
typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned int		uint32;
typedef unsigned long long	uint64;


#ifndef ORBIS

	//glu is outdated and i dont have it anyway
	#ifndef GLEW_NO_GLU
	#define GLEW_NO_GLU
	#endif
	//because im including glew.c instead of linking to the lib/dll
	#ifndef GLEW_STATIC
	#define GLEW_STATIC
	#endif

	#include "GL/glew.h"

	#ifdef __WINDOWS__
	#include "GL/wglew.h"
	#endif
	#ifdef __LINUX__
	#include "GL/glxew.h"
	#endif





	//#define __WINDOWS__




	//#define USE_SOLOUD
	#define USE_SDL_MIXER

	///-----------------------------
	///SDL libs
	///-----------------------------
	#include "SDL.h"

	//disable GL extensions through SDL, use glew instead
	#define NO_SDL_GLEXT
	#include "SDL_opengl.h"

	#define BYTE_RED 2
	#define BYTE_GREEN 1
	#define BYTE_BLUE 0

	#include "SDL_mixer.h"
	#include "SDL_ttf.h"
	#include "SDL_image.h"
	#include "SDL_net.h"

	//#include "SDL2_rotozoom.h"
	//#include "SDL2_framerate.h"
	//#include "SDL2_gfxPrimitives.h"
	//#include "SDL2_imageFilter.h"

	//#include "SDL_stbimage.h"
	//#include "stb_image.h"
	//#include "stb_image_resize.h"
	//#include "stb_image_write.h"
	//#include "stb_truetype.h"

	//#include "DG_misc.h"
	//#include "imgui.h"



#else



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//#define _USE_MATH_DEFINES
#include <math.h>
#include <vectormath.h>
#include <vector>
#include <stdint.h>
#include <map>
#include <locale>
#include <codecvt>


#include <pad.h>

#include <scebase.h>
#include <kernel.h>
#include <net.h>
#include <rudp.h>

#include <libsysmodule.h>
#include <libnetctl.h>
#include <scebase_common.h>


#include <system_service.h>
#include <sampleutil.h>
#include <app_content.h>
#include <game_live_streaming.h>
#include <np/np_common.h>



//#include <gnmx.h>
#include <video_out.h>
#include "toolkit/toolkit.h"
#include "toolkit/geommath/geommath.h"
//#include "../common/allocator.h"
//#include "../common/shader_loader.h"

//#include "std_cbuffer.h"


#include <external/lua.hpp>





#include <camera.h>


#include "util/util.h"


#include <sampleutil.h>
#include <sampleutil/sampleutil_common.h>
#include <sampleutil/audio.h>
#include <sampleutil/system.h>
#include <sampleutil/skeleton.h>
#include <sampleutil/debug/menu.h>
#include <sampleutil/debug/console.h>

#include <sampleutil/graphics.h>
#include <sampleutil/graphics/constant.h>
#include <sampleutil/graphics/program.h>
#include <sampleutil/graphics/image.h>
#include <sampleutil/graphics/loader.h>
#include <sampleutil/graphics/buffer.h>
#include <sampleutil/graphics/context.h>
#include <sampleutil/graphics/effect.h>
#include <sampleutil/graphics/platform.h>
#include <sampleutil/graphics/sprite.h>

//namespace sce
//{
//	namespace SampleUtil
//	{
//		namespace Graphics
//		{
//			namespace Collada
//			{
//				namespace Dae
//				{
//
//					namespace Common
//					{
//
//						struct Bind;
//
//					}
//				}
//			}
//		}
//	}
//}
#include <sampleutil/graphics/collada.h>
#include <sampleutil/graphics/platform_gnm/buffer_internal_gnm.h>
#include <sampleutil/graphics/platform_gnm/gnm_internal.h>
#include <sampleutil/graphics/platform_gnm/program_internal_gnm.h>
#include <sampleutil/graphics/platform_gnm/constant_internal_gnm.h>
#include <sampleutil/graphics/platform_gnm/context_internal_gnm.h>
#include <sampleutil/graphics/platform_gnm/font_orbis.h>
#include <sampleutil/graphics/platform_gnm/loader_internal_gnm.h>



#include <sampleutil/input/controller_common.h>
#include <sampleutil/input/pad_common.h>



#include "system/tutorial_shooting_game_trc_compliant/single_user/game_scene.h"
#include "system/tutorial_shooting_game_trc_compliant/single_user/player_save_data.h"
#include "system/tutorial_shooting_game_trc_compliant/common/game_object.h"
#include "system/tutorial_shooting_game_trc_compliant/common/service.h"
#include "system/tutorial_shooting_game_trc_compliant/common/util.h"
#include "system/tutorial_shooting_game_trc_compliant/common/config.h"
#include "system/tutorial_shooting_game_trc_compliant/common/game_log_manager.h"



namespace vecmath = sce::Vectormath::Simd::Aos;
namespace ssg = sce::SampleUtil::Graphics;
namespace ssgi = sce::SampleUtil::Graphics::Impl;
namespace sss = sce::SampleUtil::System;
namespace cu = common::Util;
namespace vm = sce::Vectormath::Simd::Aos;
namespace ssin = sce::SampleUtil::Input;
namespace ui = common::Util::Ui;
namespace cg = common::Game;

#define SINGLE_USER_GAME_MP4_FILE_NAME	( SCE_VIDEO_RECORDING_PATH_GAME "shooting_game_single.mp4" )



#endif

using namespace std;







typedef unsigned char u8;


class ByteArray
{
private:
	std::vector<u8> v;
public:
	u8* bytes = nullptr;
	unsigned int len = 0;

	ByteArray(u8* bytes, unsigned int len)
	{
		if (bytes && len > 0)
		{
			v.assign(bytes, bytes + len);
		}
		this->bytes = v.data();
		this->len = (unsigned int)v.size();
	}

	ByteArray(unsigned int len)
	{
		v.resize(len, 0);
		this->bytes = v.data();
		this->len = len;
	}

	ByteArray(const ByteArray& other)
	{
		v = other.v;
		bytes = v.data();
		len = (unsigned int)v.size();
	}

	ByteArray& operator=(const ByteArray& other)
	{
		if (this != &other)
		{
			v = other.v;
			bytes = v.data();
			len = (unsigned int)v.size();
		}
		return *this;
	}

	u8* data()
	{
		return v.data();
	}

	long long size()
	{
		return v.size();
	}
};

class IntArray
{
private:
	std::vector<unsigned int> v;
public:
	unsigned int* ints = nullptr;
	unsigned int len = 0;

	IntArray(unsigned int* ints, unsigned int len)
	{
		if (ints && len > 0)
		{
			v.assign(ints, ints + len);
		}
		this->ints = v.data();
		this->len = (unsigned int)v.size();
	}
	IntArray(unsigned int len)
	{
		v.resize(len, 0);
		this->ints = v.data();
		this->len = len;
	}

	IntArray(const IntArray& other)
	{
		v = other.v;
		ints = v.data();
		len = (unsigned int)v.size();
	}

	IntArray& operator=(const IntArray& other)
	{
		if (this != &other)
		{
			v = other.v;
			ints = v.data();
			len = (unsigned int)v.size();
		}
		return *this;
	}

	unsigned int* data()
	{
		return v.data();
	}

	long long size()
	{
		return v.size();
	}
};



#ifndef ORBIS
typedef struct
{
	int image_w;
	int image_h;
	int texture_w;
	int texture_h;
	GLuint texture_id;
} texture_STRUCT;


typedef struct
{
	string text;
	float x;
	float y;
	int width;
	//SDL_Color color;
} DEBUG_overlay_STRUCT;



struct GFX
{
	string FileName;// [128];
	int* indexed_gfx_data;
	int data_size_x;
	int data_size_y;

	int texture_size_x;
	int texture_size_y;

	int IndexInCachedTextureIDArray;

	bool shadow; //this is used to decide whether the texture gfx will be generated with a shadow or not

	bool hq2x; //this is needed because sprites can have their own scaling, and hq2x textures are all drawn at 0.5x by default and need the hq2x palette

	bool kid;//set on load based on size, used because kids/adults/cars need a larger texture for shadows, since the kid already fills a 32*64 texture, it creates a 32*128 one instead

	bool adult;

	bool car;
	bool bike;//car or bike will generate random alternate colors from the texture by messing with color channels. when creating a car or bike sprite, set the frame accordingly to choose a color

	bool generic;//this should somehow generate random color sets of clothing from the greyscale people. not sure how yet, especially with hq2x, i would need to output with outfit colors and then manually adjust the hq2x palette.

	int content_size_x;
	int content_size_y;
}; //this replaces gfx data

   //const GFX GFX_INIT = {"hello",NULL,0,0,-1,0};


struct SPRITE
{
	GLuint texture_id;

	GFX* gfx;

	int alpha;
	int layer;
	float scale;
	float screen_x;
	float screen_y;

	//bool draw_full_texture;

	int draw_size_x;
	int draw_size_y;//this is used to determine whether the shadow is clipped or not


					//cached or volatile? probably dont need this


					//PLAYER_gfx_slot_alpha need alpha, but it should just be per sprite, shouldnt it?

					//car
					//kid
					//bike

					//GFX struct? //if i store the gfx in here, i wont need to send in the GFX for every update_gfx_slot, i can just use NULL!


					//frames
					//layer/priority

					//zoom/getScale
					//screenx
					//screeny
					//alpha?
}; //this replaces sprite id and gfx slot, the only reason for having this is so i can index them in an array and z-order them, and then draw them in order during render

#endif

enum class RenderOrder
{
	GROUND,
	ABOVE,

	ABOVE_TOP, //over overlayer, underneath lights

	//sprites over top
	//captions
	//overlay under lights
	//stadium screen

	//lights

	//should have birds here?

	SPRITE_DEBUG_OUTLINES,
	SPRITE_DEBUG_INFO,
	OVER_TEXT,
	OVER_GUI,
	CONSOLE,

};

#ifdef ORBIS
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-function"
#endif
static RenderOrder RenderOrderValueOf(string s)
{
	if (s == "GROUND")return RenderOrder::GROUND;
	if (s == "ABOVE")return RenderOrder::ABOVE;
	if (s == "ABOVE_TOP")return RenderOrder::ABOVE_TOP;
	if (s == "SPRITE_DEBUG_OUTLINES")return RenderOrder::SPRITE_DEBUG_OUTLINES;
	if (s == "SPRITE_DEBUG_INFO")return RenderOrder::SPRITE_DEBUG_INFO;
	if (s == "OVER_TEXT")return RenderOrder::OVER_TEXT;
	if (s == "OVER_GUI")return RenderOrder::OVER_GUI;
	if (s == "CONSOLE")return RenderOrder::CONSOLE;
	return RenderOrder::GROUND;
}
#ifdef ORBIS
#pragma clang diagnostic pop
#endif

class Info
{
public:
	string label = "";
	string tip = "";
	Info(string label, string tip)
	{
		this->label = label;
		this->tip = tip;
	}
};

   //#include "soloud.h"
   //#include "soloud_wav.h"
   //#include "soloud_modplug.h"
   //#include "soloud_wavstream.h"


   //#include "SDL_config_lib.h"

   //extern "C"
   //{
   //#include "../lib/ini/iniparser.h"
   //#include "../lib/ini/textfile.h"
   //}

   //-----------------------------
   //defines
   //-----------------------------
#define GL_TEXTURE_CROP_RECT_OES 0



#endif