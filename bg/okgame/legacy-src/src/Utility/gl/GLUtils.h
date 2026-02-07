//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------
#pragma once
#include "bobtypes.h"
#include "src/Utility/HashMap.h"
#include "src/Utility/ArrayList.h"
#include <memory>


#ifdef ORBIS
#include "src/orbis/SDL/SDL_blit.h"



#include <piglet\piglet.h>
#include <EGL\egl.h>
#include <GLES2\gl2.h>
#include <piglet\piglet.h>



#endif

class Logger;
class BobTexture;


class GLUtils
{
public:

	static bool ZOOMlock;
	static float ZOOM;
	static float ZOOMto;
public:
	static Logger log;
private:
	static bool antiAlias;
public:
	static int texturesLoaded;
	static long long textureBytesLoaded;
	static shared_ptr<BobTexture> blankTexture;
	static shared_ptr<BobTexture> boxTexture;

	static float globalDrawScale;
	static shared_ptr<BobTexture> rect;


	static GLfloat* box;
	static GLfloat* col;
	static GLfloat* tex;


#ifndef ORBIS

	static SDL_Window *window;
	static SDL_Renderer *renderer;
	//static unsigned char* rgba_fbo_data; //framebuffer array
	//static unsigned char* filtered_rgba_fbo_data;

	//static bool GLOBAL_bg_layer_enabled[4];
	//static bool GLOBAL_sprite_layer_enabled;
	//static int fade_alpha;
	//static int fade_layer;
	//static int fade_vbl_counter;
	static SDL_Surface SDLSurface_screen;

	static SDL_DisplayMode currentDisplayMode;// = new SDL_DisplayMode();
	static ArrayList<SDL_DisplayMode*> displayModes;// = new ArrayList<SDL_DisplayMode*>();

	static SDL_DisplayMode getCurrentDisplayMode();
	static ArrayList<SDL_DisplayMode*> getAvailableDisplayModes();

	static void draw_sprite(SPRITE* s);
	static void gl_draw_flipped(GLuint textureid, float x, float y, float w, float h);
	static void draw_texture(GLuint textureid, float x, float y, float w, float h);
	static void draw_texture_alpha(GLuint textureid, float x, float y, float w, float h, float tw, float th, float f, float a);
	
	static void draw_texture_struct(texture_STRUCT* PLAYER_TEXTURE, float x, float y);
	
#else

#endif


#ifdef ORBIS


	static EGLSurface surface;
	static EGLDisplay display;

	static shared_ptr<BobTexture> createBobTextureFromRGBAData(sce::SampleUtil::Graphics::GraphicsLoader *loader, string textureName, int imageWidth, int imageHeight, ByteArray* data);
#endif



	static GLuint createTextureID();


	static uint32_t rmask;
	static uint32_t gmask;
	static uint32_t bmask;
	static uint32_t amask;
	static shared_ptr<BobTexture> loadTextureFromSurface(string filename, SDL_Surface* surface);

	GLUtils();
	static void bindTexture(BobTexture* bob_texture);
	static void old_clear();
	static void old_render();

	static HashMap<string, shared_ptr<BobTexture>> textureCache;
	static void clearCache(const string &name);// Remove a particular named image from the cache
	static void clearCache();
	
	static shared_ptr<BobTexture> getTextureFromData(string textureName, int imageWidth, int imageHeight, ByteArray* data);
	static void updateTexture(shared_ptr<BobTexture> texture, int x, int y, int w, int h, u8* data);
	static shared_ptr<BobTexture> getTextureFromPNGAbsolutePath(string filename);
	static shared_ptr<BobTexture> getTextureFromPNGExePath(string filename);

	static void draw_black_overlay();
	static void gl_draw_sprites(int layer);
	static void set_zoom();
	static void checkSDLError(const string &whereErrorOccurredString);
	static void checkGLError(const string &whereErrorOccurredString);
	static void e(const string &whereErrorOccurredString);
	static void e();
	
	static GLuint CreateProgramFromShaders(GLuint vertexId, GLuint fragmentId);
	static GLuint CreateProgramFromBinary(const unsigned char* pVSBinary, int nVSLength, const unsigned char* pFSBinary, int nFSLength);
	//static bool makeShaderBinary(const string& name, int shaderProgram, const string& vertPath, const string& fragPath);



	static void cleanup();
	static int getOutlinedTextWidth(string cs);
	static void setDefaultTextureParams();
	static void drawTexture(BobTexture* texture, float sx0, float sy0, int filter);
	static void drawTexture(BobTexture* texture, float sx0, float sy0, float alpha, int filter);
	static void drawTexture(BobTexture* texture, float sx0, float sx1, float sy0, float sy1, float alpha, int filter);
	static void drawTexture(BobTexture* texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter);
	static void drawTexture(int textureID, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter);
	static void drawTexture(float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float alpha, int filter);
	static void drawTexture(BobTexture* texture, float tx0, float tx1, float ty0, float ty1, float sx0, float sx1, float sy0, float sy1, float r, float g, float b, float a, int filter);
	static void drawTexture(float textureX0, float textureX1, float textureY0, float textureY1, float screenX0, float screenX1, float screenY0, float screenY1, float r, float g, float b, float a, int filter);
	static void drawOutlinedString(const string& text, float screenX, float screenY, BobColor* color);
	//static void drawOutlinedString(float screenX0, float screenY0, const string& text, BobColor* color);
	static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b);
	static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b);
	static void drawLine(float screenX0, float screenY0, float screenX1, float screenY1, float r, float g, float b, float a);
	static void drawArrowLine(float screenX0, float screenY0, float screenX1, float screenY1, int r, int g, int b);
	static void drawBox(float screenX0, float screenX1, float screenY0, float screenY1, int r, int g, int b);
	static void drawFilledRect(int ri, int gi, int bi, float screenX0, float screenX1, float screenY0, float screenY1, float alpha);
	static void drawFilledRectXYWH(float x, float y, float width, float height, float r, float g, float b, float a);
	static void drawLine(float x1, float y1, float x2, float y2, int thickness);

	static int monitorWidth;// = 0;
	static int monitorHeight;// = 0;
	static int windowWidth;
	static int windowHeight;
	static int lastWindowWidth;// = 0;
	static int lastWindowHeight;// = 0;

	static int getRealWindowWidth();
	static int getRealWindowHeight();
	static int getViewportWidth();
	static int getViewportHeight();
	static int getMonitorWidth();
	static int getMonitorHeight();
	static void setFullscreenCompatibleDisplayMode(int width, int height, bool fullscreen);
	static bool usingVSync;
	static bool disableVSync;
	static bool noVSync_UpdateAndRenderEveryFrame;
	static bool noVSync_DelayOff;


	static bool useShaders;
	static GLuint lightShader;
	static GLuint colorShader;
	static ArrayList<Integer*> bgShaders;
	static int bgShaderCount;

#ifdef ORBIS
	static GLuint uProgram;
#endif
	static int glVersionMajor;
	//static bool useFBO;

	static bool bgShaderFBOTextureToggle;// = false;
	static float bloomIntensity;// = false;


	static GLuint gaussianShader;
	static GLuint bloomMaskShader;
	static GLuint bloomShader;

	static GLuint postColorFilterFBO;
	static GLuint postColorFilterFBO_Texture_Attachment0;
	static GLuint postColorFilterFBO_Texture_Attachment1_PreLighting;

	static GLuint preColorFilterFBO;
	static GLuint preColorFilterFBO_Texture_Attachment0;
	static GLuint preColorFilterFBO_Texture_Attachment1_BloomMask;

	static GLuint bobsGame_mainGameFBO;
	static GLuint bobsGame_mainGameFBO_Texture_Attachment0;
	static GLuint bobsGame_mainGameFBO_Texture_Attachment1_BloomMask;

	static GLuint bobsGame_bloomFBO;
	static GLuint bobsGame_bloomFBO_PingPongBlur_Texture_Attachment0;
	static GLuint bobsGame_bloomFBO_PingPongBlur_Texture_Attachment1;



	static GLuint bobsGame_bgShaderFBO;
	static GLuint bobsGame_bgShaderFBO_Texture_Attachment0;
	static GLuint bobsGame_bgShaderFBO_Texture_Attachment1;


	static int bobsGameFBO_Width;
	static int bobsGameFBO_Height;
	
	

	static int GLOBAL_FRAMEBUFFER_FILTER_TYPE;
	static int DEFAULT_SHADER_FBO_FILTER;// = -1;
	static int DEFAULT_ND_FBO_FILTER;// = -1;
	static int DEFAULT_BLOOM_FBO_FILTER;// = -1;

	static const int FILTER_FBO_LINEAR_NO_MIPMAPPING = -2;
	static const int FILTER_FBO_NEAREST_NO_MIPMAPPING = -1;
	static const int FILTER_NEAREST = 0;
	static const int FILTER_LINEAR = 1;
	static float SHADER_FBO_SCALE;
	static float FBO_SCALE;
	static float BLOOM_FBO_SCALE;
	static void setRealWindowViewport();
	static void setPostColorFilterViewport();
	static void setPreColorFilterViewport();
	static void setBobsGameMainFBOFilterViewport();
	static void setBloomViewport();
	static void setShaderViewport();
	

	static void setPreColorFilterFBO();
	static void setPostColorFilterFBO();
	static void setShaderFBO();
	static void setBobsGameMainFBO();
	static void setBobsGameMaskFBO();
	static void setBloomFBO();
	static void unsetShaderFBO();
	static void setMainScreenFB();
	static void fillBufferWithBlack();
	static void fillBufferWithTransparency();
	static void drawPreColorFilterFBOTexture();
	static void drawPostColorFilterFBOTexture();
	static void drawShaderFBOTexture();
	static void drawBobsGameFBO(float x0, float x1, float y0, float y1);
	static void drawBobsGameMainFBOTexture0();
	static void drawBobsGameFBOBloomMaskTexture();
	static void drawBobsGameFBOBloomMaskTexture1();
	static void setBlendSrcAlpha();
	static void drawBlocksUsingBloomShader();

	static void disableBlend();
	static void enableBlend();
	static void setupBloomThresholdShader();
	static void doBlurShader();
	

	static void initGL(char* windowName);
private:
	static void attachTextureToFBO(int attachment, int textureID);
public:
	static bool ARBFBO;
	static void bindFBO(int fboID);
	static void drawIntoFBOAttachment(int i);
	static int genFBO();
	static int setupFBOTexture(int tex, int width, int height);
	static bool ARBShader;
	//static int createProgramObject();
	static const int FRAG = 0;
	static const int VERT = 1;
private:
	static void loadShaderBinary(const string& filename, GLuint shaderID);
	static void compileShaderFromText(const string& filename, GLuint shaderID);
public:
	static bool makeShader(const string& name, GLuint* shaderProgram, const string& vertPath, const string& fragPath, bool isBinary = false);
	static void useShader(int shader);
	static bool fullscreen;// = false;
	static void toggleFullscreen();
	static void doResize();
	static void resizeBobsGameFBO(float w, float h);
	static void setBlendMode(int src, int dst);
	static void setShaderVar1i(int shader, char* name, int i);
	static void setShaderVar1f(int shader, char* name, float f);
	static void setShaderVar2f(int shader, char* name, float f1, float f2);
};
