package com.bobsgame.client.engine.map;



//import static org.lwjgl.opengl.GL11.GL_COLOR_BUFFER_BIT;
//import static org.lwjgl.opengl.GL11.GL_ONE;
//import static org.lwjgl.opengl.GL11.GL_ONE_MINUS_SRC_ALPHA;
//import static org.lwjgl.opengl.GL11.GL_SRC_ALPHA;
//import static org.lwjgl.opengl.GL11.GL_TEXTURE_2D;
//import static org.lwjgl.opengl.GL11.GL_TRUE;
//import static org.lwjgl.opengl.GL11.glBindTexture;

//import static org.lwjgl.opengl.GL11.glClear;
//import static org.lwjgl.opengl.GL11.glClearColor;
//import static org.lwjgl.opengl.GL11.glDisable;
//import static org.lwjgl.opengl.GL11.glDrawBuffer;
//import static org.lwjgl.opengl.GL11.glEnable;
//import static org.lwjgl.opengl.GL11.glTexParameteri;
//import static org.lwjgl.opengl.GL12.GL_TEXTURE_BASE_LEVEL;
//import static org.lwjgl.opengl.GL12.GL_TEXTURE_MAX_LEVEL;
//import static org.lwjgl.opengl.GL13.GL_TEXTURE0;
//import static org.lwjgl.opengl.GL13.GL_TEXTURE1;
//import static org.lwjgl.opengl.GL13.glActiveTexture;
//import static org.lwjgl.opengl.GL14.GL_GENERATE_MIPMAP;
//import static org.lwjgl.opengl.GL20.glGetUniformLocation;
//import static org.lwjgl.opengl.GL20.glUniform1f;
//import static org.lwjgl.opengl.GL20.glUniform1i;
//import static org.lwjgl.opengl.GL20.glUseProgram;


//import static org.lwjgl.opengl.GL42.*;
//import static org.lwjgl.opengl.GL41.*;
//import static org.lwjgl.opengl.GL40.*;
//import static org.lwjgl.opengl.GL33.*;
//import static org.lwjgl.opengl.GL32.*;
//import static org.lwjgl.opengl.GL31.*;
//import static org.lwjgl.opengl.GL30.*;
import static org.lwjgl.opengl.GL13.*;
import static org.lwjgl.opengl.GL11.*;


import java.util.ArrayList;
import java.util.Vector;

import java.util.concurrent.ConcurrentHashMap;

import org.slf4j.LoggerFactory;

import com.bobsgame.client.Texture;

import ch.qos.logback.classic.Logger;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.LWJGLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.entity.Entity;
import com.bobsgame.client.engine.entity.Sprite;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.shared.MapData.RenderOrder;

//import se.krka.kahlua.converter.*;
//import se.krka.kahlua.integration.LuaCaller;
//import se.krka.kahlua.integration.annotations.LuaMethod;
//import se.krka.kahlua.integration.expose.LuaJavaClassExposer;
//import se.krka.kahlua.integration.expose.ReturnValues;
//import se.krka.kahlua.j2se.J2SEPlatform;
//import se.krka.kahlua.luaj.compiler.LuaCompiler;
//import se.krka.kahlua.vm.KahluaTable;
//import se.krka.kahlua.vm.KahluaThread;
//import se.krka.kahlua.vm.LuaClosure;

//=========================================================================================================================
public class MapManager extends EnginePart
{//=========================================================================================================================

	public Vector<Map> mapList = new Vector<Map>();
	public ConcurrentHashMap<String,Map> mapByNameHashMap = new ConcurrentHashMap<String,Map>();
	public ConcurrentHashMap<Integer,Map> mapByIDHashMap = new ConcurrentHashMap<Integer,Map>();

	public static Logger log = (Logger) LoggerFactory.getLogger(MapManager.class);


	public Map currentMap;
	private Map lastMap;










//	private final KahluaConverterManager converterManager = new KahluaConverterManager();
//	private final J2SEPlatform platform = new J2SEPlatform();
//	private final KahluaTable env = platform.newEnvironment();
//	private final KahluaThread thread = new KahluaThread(platform, env);
//	private final LuaCaller caller = new LuaCaller(converterManager);
//
//	private final LuaJavaClassExposer exposer = new LuaJavaClassExposer(converterManager, platform, env);

	public static boolean useThreads = true;
	public static boolean generateHQ2XChunks = false;
	public static boolean loadTexturesOnDemand = true;



	//textures mapped to light filenames
	public ConcurrentHashMap<String,Texture> lightTextureHashMap = new ConcurrentHashMap<String,Texture>();


	//hashtable (threadsafe) mapped to light filename, and boolean array[1] set whether it exists (so multiple threads don't check if file exists at same time)
	public ConcurrentHashMap<String,boolean[]> lightTextureFileExistsHashtable = new ConcurrentHashMap<String,boolean[]>();


	public Door doorEntered=null;
	public Door doorExited=null;

	public WarpArea warpEntered=null;
	public WarpArea warpExited=null;


	public float drawAngle = 0;//TODO

	public float hue = 1.0f;
	public float saturation = 1.0f;
	public float brightness = 1.0f;
	public float contrast = 1.0f;
	public float gamma = 1.0f;
	public boolean grayscale = false;
	public boolean effects8Bit;//TODO
	public boolean effectsInverted;//TODO
	public boolean effectsBlackAndWhite;//TODO

	//=========================================================================================================================
	public MapManager(Engine g)
	{//=========================================================================================================================
		super(g);


		//KahluaNumberConverter.install(converterManager);


		//KahluaTable javaBase = platform.newTable();
		//env.rawset("Java", javaBase);
		//exposer.exposeLikeJavaRecursively(DebugConsole.class, javaBase);
		//exposer.exposeLikeJavaRecursively(Player.class, javaBase);
		//exposer.exposeLikeJavaRecursively(mapMan().class, javaBase);
		//exposer.exposeLikeJavaRecursively(g.class, javaBase);
		//exposer.exposeLikeJavaRecursively(Entity.class, javaBase);
		//exposer.exposeGlobalFunctions(G.luaAPI);

		//LuaClosure closure = LuaCompiler.loadstring("Java.DebugConsole.add('hello');", "", env);
		//caller.protectedCall(thread, closure);


	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================


	}

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		if(currentMap!=null)
		{

			//should setscreen for entities AFTER map adjusts itself
			fadeOutAndReleaseLastMap();

			currentMap.update();

			//these can be in any order, since they only rely on map_cam_xy which is set in updateLogic
			currentMap.updateLastKnownScreenXYBasedOnCamera();//this is 0-map_cam_xy

		}

	}

	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================

		//Iterator<Map> maps = Game().mapByNameHashMap.values().iterator();


		//while(maps.hasNext())
		{

			try
			{
				//Map m = maps.next();


				if(MapManager.useThreads)
				{
					if(Map.generatePNGExecutorService!=null)Map.generatePNGExecutorService.shutdownNow();//.awaitTermination(30, TimeUnit.SECONDS);
					if(Map.generateLightPNGExecutorService!=null)Map.generateLightPNGExecutorService.shutdownNow();//.awaitTermination(30, TimeUnit.SECONDS);
					if(Sprite.generatePNGExecutorService!=null)Sprite.generatePNGExecutorService.shutdownNow();//.awaitTermination(30, TimeUnit.SECONDS);
					//if(m.generateHQ2XPNGExecutorService!=null)m.generateHQ2XPNGExecutorService.shutdownNow();//awaitTermination(30, TimeUnit.SECONDS);
				}
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}




	}








	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		if(currentMap==null)return;



		if(LWJGLUtils.useFBO && Engine() instanceof ClientGameEngine)
		{

			LWJGLUtils.bindFBO(LWJGLUtils.mainFBO);//set the framebuffer object to the MAIN FBO

			LWJGLUtils.drawIntoFBOAttachment(0);//set which framebuffer object to draw into (whatever buffer is set with glBindFramebufferEXT)

			//clear the main FBO
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			//DONE: need to resize the fbo texture when the screen size changes

			//DONE: also need to send the fbo size into the lights shader, it is currently hardcoded



			renderLastMap();

			currentMap.render(RenderOrder.GROUND);
			currentMap.renderEntities(RenderOrder.GROUND);
			CaptionManager().render(RenderOrder.GROUND);


			LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			CinematicsManager().render(RenderOrder.GROUND);
			LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			//LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE);
			currentMap.render(RenderOrder.ABOVE);
			currentMap.renderEntities(RenderOrder.ABOVE);
			currentMap.renderEntities(RenderOrder.ABOVE_TOP);//birds? //TODO should have something OVER lights as well!
			//LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


			//if(!Keyboard.isKeyDown(Keyboard.KEY_COMMA))
			LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
			CinematicsManager().render(RenderOrder.ABOVE);//screen overlay under lights
			//if(!Keyboard.isKeyDown(Keyboard.KEY_PERIOD))
			LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			ClientGameEngine().stadiumScreen.render();

//			if(Keyboard.isKeyDown(Keyboard.KEY_LBRACKET))LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
//			else
//			LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			if(LWJGLUtils.useShader)
			{

				//DONE: this is reading from the FBO texture while writing to the FBO which may be undefined.
				//i may need to use "ping pong" rendering:
				//attach to TEMP FBO
				//draw mainFBO texture into TEMP FBO
				//attach to mainFBO
				//bind TEMP FBO texture into shader
				//draw as many lights as i can that don't overlap, screen blended with the TEMP FBO texture
				//repeat.
				//i may also be able to keep the FBO as one object and just switch textures

				boolean flip=true;

				for(int i=0; i<currentMap.sortedLightsLayers.size(); i++)
				{
					ArrayList<Light> thisLayer = currentMap.sortedLightsLayers.get(i);


					if(flip==true)
					{
						//flip FBO attachment buffers


						//switch to LIGHTS buffer attachment
						LWJGLUtils.drawIntoFBOAttachment(1);//draws into lightFBOTextureID
						glClear(GL_COLOR_BUFFER_BIT);

						//draw the main FBO texture into the LIGHTS buffer attachment
						GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0, 1, 1, 0, 0, (int)(LWJGLUtils.SCREEN_SIZE_X), 0, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

						//switch to MAIN buffer attachment
						LWJGLUtils.drawIntoFBOAttachment(0);//draws into mainFBOTextureID
					}

					LWJGLUtils.useShader(LWJGLUtils.lightShader);

					//set the LIGHTS FBO texture to texture 0, we drew the main FBO (maps and sprites) into it and we are going to use it to blend
					glActiveTexture(GL_TEXTURE0);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, LWJGLUtils.mainFBO_lightTexture);


					glActiveTexture(GL_TEXTURE1);//switch to texture 1, we are going to bind the light textures to this when we draw them.
					glEnable(GL_TEXTURE_2D);


					LWJGLUtils.setShaderVar1i(LWJGLUtils.lightShader,"Tex0",0);
					LWJGLUtils.setShaderVar1i(LWJGLUtils.lightShader,"Tex1",1);
					LWJGLUtils.setShaderVar1f(LWJGLUtils.lightShader,"width",LWJGLUtils.SCREEN_SIZE_X);
					LWJGLUtils.setShaderVar1f(LWJGLUtils.lightShader,"height",LWJGLUtils.SCREEN_SIZE_Y);



					flip = false;

					//now we render the lights, we bind the light texture to texture unit 1 and draw them into the main FBO,
					//blending with texture unit 1 which is the lights FBO with maps and sprites drawn in it.

					//we will draw/blend all the lights that don't overlap into the mainFBO texture
					//then we will draw that blended layer back to the lightsFBO so we can blend another layer on top of it without ugly blending artifacts.
					//this is "ping pong" rendering technique.
					for(int n=0; n<thisLayer.size(); n++)
					{
						Light l = thisLayer.get(n);
						if(l.name().contains("mover")==false)//skip mover lights, draw them afterwards.
						{
							if(l.renderLight()==true)flip=true;
						}
					}

					//disable texture2D on texture unit 1
					glActiveTexture(GL_TEXTURE1);
					glDisable(GL_TEXTURE_2D);

					//switch back to texture unit 0
					glActiveTexture(GL_TEXTURE0);

					LWJGLUtils.useShader(0);

				}


				if(currentMap!=null)
				{
					if(currentMap.currentState!=null)
					{
						//draw mover lights after finished drawing blended lights.
						for(int i=0; i<currentMap.currentState.lightList.size(); i++)
						{
							Light l = currentMap.currentState.lightList.get(i);
							if(l.name().contains("mover"))
							{
								l.renderLight();
							}
						}
					}
				}


				LWJGLUtils.bindFBO(0);//set the framebuffer back to the screen buffer
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);



				setEffectsShaderEffects();

				setTextureRotation();


				//draw the framebuffer with the lights drawn into it into the screen buffer
				//if(!Keyboard.isKeyDown(Keyboard.KEY_SLASH))
				LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);//this fixes the small shadow problems, and also makes the doorknob glow brighter.
				GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0, 1, 1, 0, 0, (int)(LWJGLUtils.SCREEN_SIZE_X), 0, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
				LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


				//set back to normal rendering
				//if(useColorShader)
				LWJGLUtils.useShader(0);

			}
			else //not using shaders
			{


				LWJGLUtils.bindFBO(0);//set the framebuffer back to the screen buffer
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

				//draw mainFBO (which contains all the map layers drawn into it) to the screen buffer
				LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
				GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0, 1, 1, 0, 0, (int)(LWJGLUtils.SCREEN_SIZE_X), 0, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
				LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				//set the framebuffer object back to mainFBO
				LWJGLUtils.bindFBO(LWJGLUtils.mainFBO);//set the framebuffer object to the MAIN FBO
				//clear the lights FBO
				glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
				glClear(GL_COLOR_BUFFER_BIT);

				//draw the lights into mainFBO
				currentMap.renderAllLightsUnsorted();

				//set the framebuffer back to the screen buffer
				LWJGLUtils.bindFBO(0);


				setFBOEffects();
				setTextureRotation();

				//draw mainFBO (which now contains lights) into the screen buffer
				LWJGLUtils.setBlendMode(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
				GLUtils.drawTexture(LWJGLUtils.mainFBO_Texture, 0, 1, 1, 0, 0, (int)(LWJGLUtils.SCREEN_SIZE_X), 0, (int)(LWJGLUtils.SCREEN_SIZE_Y), 1.0f, GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);
				LWJGLUtils.setBlendMode(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			}

		}
		else //not using FBO
		{

			setNonFBOEffects();
			setTextureRotation();

			renderLastMap();


			currentMap.render(RenderOrder.GROUND);
			currentMap.renderEntities(RenderOrder.GROUND);
			CinematicsManager().render(RenderOrder.GROUND);
			CaptionManager().render(RenderOrder.GROUND);
			currentMap.render(RenderOrder.ABOVE);
			currentMap.renderEntities(RenderOrder.ABOVE);
			currentMap.renderEntities(RenderOrder.ABOVE_TOP);
			CinematicsManager().render(RenderOrder.ABOVE);

			ClientGameEngine().stadiumScreen.render();


			currentMap.renderAllLightsUnsorted();

		}


		//mapManager.currentMap.drawMiniMap();


	}


	//=========================================================================================================================
	public void renderLastMap()
	{//=========================================================================================================================

		if(lastMap!=null)
		{

			lastMap.render(RenderOrder.GROUND, true);
			lastMap.renderEntities(RenderOrder.GROUND);


//			for(int i=0;i<lastMap.doorList.size();i++)
//			{
//				Door d = lastMap.doorList.get(i);
//
//				{
//					if(d!=doorEntered)
//					{
//						d.render(lastMap.alpha);
//					}
//				}
//
//			}

			lastMap.render(RenderOrder.ABOVE, true);
			lastMap.renderEntities(RenderOrder.ABOVE);
			lastMap.renderEntities(RenderOrder.ABOVE_TOP);
		}


	}


	//=========================================================================================================================
	/**for drawing any map entities over text*/
	public void renderEntities(RenderOrder layer)
	{//=========================================================================================================================

		if(currentMap!=null)
		currentMap.renderEntities(layer);
	}

	//=========================================================================================================================
	public void setFBOEffects()
	{//=========================================================================================================================

		//TODO: hacks for stuff like grayscale, etc. without using shaders.
	}

	//=========================================================================================================================
	public void setNonFBOEffects()
	{//=========================================================================================================================
		//TODO: figure out what doesnt have FBO support. maybe use PBO instead??

	}

	//=========================================================================================================================
	public void setEffectsShaderEffects()
	{//=========================================================================================================================
		boolean useColorShader = false;//TODO: optimise this, it is too slow for release.
		//maybe use screen filters instead or overlays or something, there has got to be a better way.
		//maybe there is a gl function for making textures grayscale
		//also there were slick/lwjgl/?? utilities for setting things like hue


		//TODO: have cinematic stuff control this.

		if(useColorShader)
		{
			LWJGLUtils.useShader(LWJGLUtils.colorShader);

			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader,"gameHue", hue);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameSaturation", saturation);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameBrightness", brightness);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameContrast", contrast);
			LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameGamma", gamma);
			if(grayscale==true)LWJGLUtils.setShaderVar1f(LWJGLUtils.colorShader, "gameSaturation", 0.0f);
			LWJGLUtils.setShaderVar1i(LWJGLUtils.colorShader, "Tex0", 0);
		}

	}

	//=========================================================================================================================
	public void setTextureRotation()
	{//=========================================================================================================================
		if(drawAngle!=0.0f)
		{
			glMatrixMode(GL_TEXTURE);
			glLoadIdentity();
			glTranslated(0.5f,0.5f,0.0f);
			glRotated(drawAngle,0.0f,0.0f,1.0f);
			glTranslated(-0.5f,-0.5f,0.0f);
			glMatrixMode(GL_MODELVIEW);
		}
	}


	//=========================================================================================================================
	public void rotateMap(int rotateDegrees)
	{//=========================================================================================================================
		drawAngle = rotateDegrees/360.0f;
	}











	//=========================================================================================================================
	public void renderDebug()
	{//=========================================================================================================================

		//org.newdawn.slick.Color.white.bind();
		//glEnable(GL_TEXTURE_2D);
		glDisable(GL_TEXTURE_2D);

		if(Engine().debugLayerEnabled==true)
		{

			currentMap.renderChunkBoxes();
			currentMap.renderHitLayer();
			currentMap.renderLightBoxes();

			currentMap.renderEntities(RenderOrder.SPRITE_DEBUG_OUTLINES);//-1 = debug boxes
			SpriteManager().renderScreenSprites(RenderOrder.SPRITE_DEBUG_OUTLINES);//-1 = debug boxes
			currentMap.renderAreaDebugBoxes();
			currentMap.renderWarpAreaDebugBoxes();



			//org.newdawn.slick.Color.white.bind();

			//debug captions
			//SlickCallable.leaveSafeBlock();//weird slick texture errors if i dont do this
			{
				currentMap.renderAreaDebugInfo();
				currentMap.renderWarpAreaDebugInfo();
				currentMap.renderEntities(RenderOrder.SPRITE_DEBUG_INFO);//-2 = debug info
				SpriteManager().renderScreenSprites(RenderOrder.SPRITE_DEBUG_INFO);//-2 = debug info
			}
			//SlickCallable.enterSafeBlock();
		}

	}

	//=========================================================================================================================
	public boolean isDayTime()
	{//=========================================================================================================================

		//TODO: hook these up to clock

		return true;

	}

	//=========================================================================================================================
	public boolean isNightTime()
	{//=========================================================================================================================
		//TODO
		return false;

	}


	//=========================================================================================================================
	public boolean isRaining()
	{//=========================================================================================================================
		// TODO
		return false;
	}


	//=========================================================================================================================
	public boolean isSnowing()
	{//=========================================================================================================================
		// TODO
		return false;
	}


	//=========================================================================================================================
	public boolean isWindy()
	{//=========================================================================================================================
		// TODO
		return false;
	}



	//=========================================================================================================================
	public boolean isFoggy()
	{//=========================================================================================================================
		// TODO
		return false;
	}



	//used to keep track of the camera offset so we can scroll the last map along with the new one
	static float lastMapCameraOffsetX = 0;
	static float lastMapCameraOffsetY = 0;
	static float lastMapScreenX = 0;
	static float lastMapScreenY = 0;

	//=========================================================================================================================
	public void fadeOutAndReleaseLastMap()
	{//=========================================================================================================================
		if(lastMap!=null)
		{
			if(lastMap.generatingAreaNotification!=null)lastMap.generatingAreaNotification = lastMap.generatingAreaNotification.delete();

			lastMap.lastKnownScreenX=lastMapScreenX+lastMapCameraOffsetX-Cameraman().x();
			lastMap.lastKnownScreenY=lastMapScreenY+lastMapCameraOffsetY-Cameraman().y();

			if(currentMap.alpha==1.0f)//when current map is completely opaque
			{
				lastMap.fadeOut();

				if(lastMap.alpha==0.0f)
				{
					lastMap.clearActiveEntityList();
					lastMap.releaseAllTextures();//TODO: this is what's causing the blip going from outside to inside i bet. test this!
					//TODO: could also try keeping the outside textures in memory if they will fit.
					lastMap = null;
				}
			}

		}

	}

	//=========================================================================================================================
	public void setTransitionOffsets()
	{//=========================================================================================================================


		float cameraOffsetX=0;
		float cameraOffsetY=0;

		if(doorEntered!=null)
		{
			//get camera offset to lastDoor+height
			cameraOffsetX = (doorEntered.x()+doorEntered.hitBoxFromLeft())-Cameraman().x();
			cameraOffsetY = (doorEntered.y()+doorEntered.hitBoxFromTop())-Cameraman().y();
		}

		if(warpEntered!=null)
		{
			//get camera offset to lastDoor+height
			cameraOffsetX = (warpEntered.x())-Cameraman().x();
			cameraOffsetY = (warpEntered.y())-Cameraman().y();
		}



		if(doorExited!=null)
		{
			//fade in door
			//doorExited.alpha=0.0f; //TODO: notice that i disabled this, it looks nicer to have the door stay opaque now with animations.

			Cameraman().setX((doorExited.x()+doorExited.hitBoxFromLeft())-cameraOffsetX);
			Cameraman().setY((doorExited.y()+doorExited.hitBoxFromTop())-cameraOffsetY);
		}
		else
		if(warpExited!=null)
		{
			Cameraman().setX((warpExited.x())-cameraOffsetX);
			Cameraman().setY((warpExited.y())-cameraOffsetY);
		}
		else
		Cameraman().setXYToTarget();

		doorExited=null;
		doorEntered=null;
		warpEntered=null;
		warpExited=null;

		if(lastMap!=null)
		{
			//so the last map can track along the current map as the camera normalizes
			lastMapScreenX = lastMap.lastKnownScreenX;
			lastMapScreenY = lastMap.lastKnownScreenY;
		}

		lastMapCameraOffsetX = Cameraman().x();
		lastMapCameraOffsetY = Cameraman().y();
	}


	//=========================================================================================================================
	public void changeMap(String mapName, int mapXPixelsHQ, int mapYPixelsHQ)
	{//=========================================================================================================================
		changeMap(mapName,mapXPixelsHQ,mapYPixelsHQ,true);
	}

	//=========================================================================================================================
	public void changeMap(String mapName, int mapXPixelsHQ, int mapYPixelsHQ, boolean updateGameSave)
	{//=========================================================================================================================

		for(int i=0;i<1;i++)
		{
			//System.runFinalization();
			//System.gc();
		}

		if(currentMap!=null)
		{
			//currentMap.unload();//this is exported by tools, lights, areas, entities are unloaded here per-map in overridden function.

			EventManager().unloadCurrentMapEvents();//this just clears the event queue and resets the execution order of event commands.
		}

		lastMap=currentMap;


		Map m = getMapByNameBlockUntilLoaded(mapName);
		if(m==null){log.error("Could not load map: "+mapName);return;}

		currentMap = m;
		currentMap.alpha=0.0f;
		currentMap.currentState = null;
		currentMap.addedEntitiesAndCharactersFromCurrentStateToActiveEntityList = false;
		currentMap.eventsAllLoadedFromServer = false;

		setTransitionOffsets();


		if(Engine() instanceof ClientGameEngine)
		{


			if(lastMap!=null)
			lastMap.activeEntityList.remove(Player());	//DONE: each map should just render its own entities, so we can fade out the last map's entities along with the map.
			//so we should actually clear the entities after the last map is faded out.
			//remove the entitymanager entirely.

			Player().setFeetAtMapXY(mapXPixelsHQ,mapYPixelsHQ);


			if(ClientGameEngine().finishedLoadEvent())
			{

				if(mapName.equals("BLANK")==false&&updateGameSave==true)
				{
					//TODO: make sure we are allowed in this room before doing this! otherwise we will be stuck.
					Network().addQueuedGameSaveUpdateRequest_S("lastKnownRoom:`"+mapName+"`,lastKnownX:`"+mapXPixelsHQ+"`,lastKnownY:`"+mapYPixelsHQ+"`");
				}

			}



		}


		//currentMap.load();//this is exported by tools, lights, areas, entities are created here per-map in overridden function.

	}

	//=========================================================================================================================
	public void changeMap(Map m, int mapXTiles1X, int mapYTiles1X)
	{//=========================================================================================================================
		changeMap(m.name(),mapXTiles1X*2*8,mapYTiles1X*2*8);

	}

	//=========================================================================================================================
	public void changeMap(Map m, Door door)
	{//=========================================================================================================================
		changeMap(m.name(),door.arrivalXPixelsHQ(),door.arrivalYPixelsHQ());

	}

	//=========================================================================================================================
	public void changeMap(Map m, Area area)
	{//=========================================================================================================================
		changeMap(m.name(),(int)(area.middleX()),(int)(area.middleY()));

	}

	//=========================================================================================================================
	public void changeMap(Map m, WarpArea area)
	{//=========================================================================================================================
		changeMap(m.name(),area.arrivalXPixelsHQ(),area.arrivalYPixelsHQ());

	}

	//=========================================================================================================================
	public void changeMap(String mapName, String areaName)
	{//=========================================================================================================================
		Map m = getMapByNameBlockUntilLoaded(mapName);
		Area a = m.getAreaOrWarpAreaByName(areaName);
		changeMap(m,a);
	}





	//=========================================================================================================================
	public Map getMapByIDBlockUntilLoaded(int id)
	{//=========================================================================================================================

		if(id==-1){log.warn("getMapByID: "+id); return CurrentMap();}


		Map m = mapByIDHashMap.get(id);

		if(m==null)
		{
			log.warn("Map did not exist in mapByIDHashMap. Blocking until loaded from network. This should never happen, we should preemptively load map data for connecting doors.");


			Network().sendMapDataRequestByID(id);


			int tries = 0;

			while(m==null)
			{

				tries++;
				if(tries>5)
				{
					log.warn("Map did not load in more than 5 seconds. Resending request.");

					tries=0;
					Network().sendMapDataRequestByID(id);
				}

				try
				{
					Thread.sleep(1000);
				}
				catch(InterruptedException e)
				{
					e.printStackTrace();
				}


				m = mapByIDHashMap.get(id);

			}

			log.warn("Map finished loading from network.");

		}

		return m;
	}



	//=========================================================================================================================
	public Map getMapByNameBlockUntilLoaded(String name)
	{//=========================================================================================================================

		if(name==null||name.equals("none")||name.equals("null")||name.length()==0){log.warn("getMapByName: "+name); return CurrentMap();}


		Map m = mapByNameHashMap.get(name);

		if(m==null)
		{
			log.warn("Map NAME: \""+name+"\" did not exist in mapNameHashMap. Blocking until loaded from network. This should never happen, we should preemptively load map data for connecting doors.");


			Network().sendMapDataRequestByName(name);


			int tries = 0;

			while(m==null)
			{

				tries++;
				if(tries>5)
				{
					log.warn("Map NAME: \""+name+"\" did not load in more than 5 seconds. Resending request.");

					tries=0;
					Network().sendMapDataRequestByName(name);
				}

				try
				{
					Thread.sleep(1000);
				}
				catch(InterruptedException e)
				{
					e.printStackTrace();
				}


				m = mapByNameHashMap.get(name);

			}

			log.warn("Map NAME: \""+name+"\" finished loading from network.");

		}

		return m;



	}

	//=========================================================================================================================
	public void requestMapDataIfNotLoadedYet(String name)
	{//=========================================================================================================================


		if(name==null||name.equals("none")||name.equals("null")||name.length()==0){log.warn("requestMapDataIfNotLoadedYet: "+name); return;}


		Map m = mapByNameHashMap.get(name);

		if(m==null)
		{
			Network().sendMapDataRequestByName(name);
		}

	}








	//=========================================================================================================================
	public MapState getMapStateByID(int id)
	{//=========================================================================================================================


		//first check the current map.
		MapState s = CurrentMap().getMapStateByID(id);

		if(s!=null)return s;


		//TODO check the other maps if we can't find this ID, this should never happen.

		return null;

	}

	//=========================================================================================================================
	public Area getAreaByID(int id)
	{//=========================================================================================================================

		// first check the current state of the current map
		if(currentMap!=null){Area a = currentMap.getAreaOrWarpAreaByTYPEID("AREA."+id); if(a!=null)return a;}

		//TODO: then check all states of current map

		//then check all states of all maps
		for(int i=0;i<mapList.size();i++)
		{
			Map m = mapList.get(i);
			for(int k=0;k<m.stateList.size();k++)
			{
				MapState s = m.stateList.get(k);
				for(int l=0;l<s.areaList.size();l++)
				{
					Area a = s.areaList.get(l);
					if(a.id()==id)return a;
				}
			}

			for(int n=0;n<m.warpAreaList.size();n++)
			{
				if(m.warpAreaList.get(n).id()==id)
				return m.warpAreaList.get(n);
			}

		}

		return null;

	}

	//=========================================================================================================================
	public Entity getEntityByID(int id)
	{//=========================================================================================================================
		//TODO: first check the current state of the current map

		//TODO: then check all states of current map

		//then check all states of all maps
		for(int i=0;i<mapList.size();i++)
		{
			Map m = mapList.get(i);
			for(int k=0;k<m.stateList.size();k++)
			{
				MapState s = m.stateList.get(k);
				for(int l=0;l<s.entityList.size();l++)
				{
					Entity a = s.entityList.get(l);
					if(a.id()==id)return a;
				}

				for(int l=0;l<s.characterList.size();l++)
				{
					Entity a = s.characterList.get(l);
					if(a.id()==id)return a;
				}

				for(int l=0;l<s.lightList.size();l++)
				{
					Entity a = s.lightList.get(l);
					if(a.id()==id)return a;
				}

			}

			for(int n=0;n<m.doorList.size();n++)
			{
				if(m.doorList.get(n).id()==id)
				return m.doorList.get(n);
			}

			for(int n=0;n<m.activeEntityList.size();n++)
			{
				if(m.activeEntityList.get(n).id()==id)
				return m.activeEntityList.get(n);
			}

		}

		for(int n=0;n<SpriteManager().screenSpriteList.size();n++)
		{
			if(SpriteManager().screenSpriteList.get(n).id()==id)
			return SpriteManager().screenSpriteList.get(n);
		}

		return null;

	}


	//=========================================================================================================================
	public Light getLightByID(int id)
	{//=========================================================================================================================
		//TODO: first check the current state of the current map

		//TODO: then check all states of current map

		//then check all states of all maps
		for(int i=0;i<mapList.size();i++)
		{
			Map m = mapList.get(i);
			for(int k=0;k<m.stateList.size();k++)
			{
				MapState s = m.stateList.get(k);
				for(int l=0;l<s.lightList.size();l++)
				{
					Light a = s.lightList.get(l);
					if(a.id()==id)return a;
				}
			}
		}

		return null;
	}


	//=========================================================================================================================
	public Door getDoorByID(int id)
	{//=========================================================================================================================

		//TODO: first check current map

		//then check all maps
		for(int i=0;i<mapList.size();i++)
		{
			Map m = mapList.get(i);

			for(int l=0;l<m.doorList.size();l++)
			{
				Door a = m.doorList.get(l);
				if(a.id()==id)return a;
			}

		}

		return null;

	}

}
