package com.bobsgame.client.engine.cinematics;

import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;
//=========================================================================================================================
public class CinematicsManager extends EnginePart
{//=========================================================================================================================



	public Letterbox letterbox = null;
	public ScreenOverlay screenOverlayOverLights=null;
	public ScreenOverlay screenOverlayUnderLights=null;
	public ScreenOverlay screenOverlayGroundLayer=null;


	//TODO: probably want to organize these effects in a linked list or something

	//need a way to make new effects at any time, or maybe could just have a lot of presets?


	//color overlays (screenfade with max opacity)

	//flashes (screenfade with fast speed)


	//screen shake: need to access cameraman, that's it

	//slow motion: need to modulate Game().ticksPassed() per frame, probably


	//lighting
	//shadows on edges of screen
	//do fps hdr light modulation when go indoor/outdoors

	//hdr, color saturation controls, etc

	//eyes closing and opening (+ blur, nice effect)

	//tv blip like android phone

	//mosaic, rotate, etc

	//darkness layer and torch

	//flicker

	//screen wipes


	//ntsc distortion
	//scanlines
	//crosshatch and glow simulate crt pixels

	//use nnedi3/eedi3 scaling?

	//motion blur

	//timeline, show places lived on map, show desk pictures, do metroid like text intro, show version of game


	//blur: render to small framebuffer, render back to screen with bilinear filter
	//OR: pixel shader
	//how to do this per-layer?
	//should never blur the text engine probably, unless it's a dizzyness thing

	//lighting effects (grayscale, sepia, filters,etc)
	//will need pixel shader or framebuffer object for these
	//research using pixel shaders, maybe that even needs framebuffer


	//rewind and fast forward



	//=========================================================================================================================
	public CinematicsManager(Engine g)
	{//=========================================================================================================================

		super(g);

		screenOverlayOverLights = new ScreenOverlay(g);
		screenOverlayUnderLights = new ScreenOverlay(g);
		screenOverlayGroundLayer = new ScreenOverlay(g);

		letterbox = new Letterbox(g);

	}
	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		screenOverlayOverLights.init();
		screenOverlayUnderLights.init();
		screenOverlayGroundLayer.init();


		letterbox.init();
	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		letterbox.update();

		screenOverlayOverLights.update();
		screenOverlayUnderLights.update();
		screenOverlayGroundLayer.update();
	}

	//=========================================================================================================================
	public void render(RenderOrder renderOrder)
	{//=========================================================================================================================
		if(renderOrder == RenderOrder.GROUND)
		{
			screenOverlayGroundLayer.render();
		}

		if(renderOrder == RenderOrder.ABOVE)
		{
			screenOverlayUnderLights.render();
		}

		if(renderOrder == RenderOrder.ABOVE_TOP)
		{
			letterbox.render();
			screenOverlayOverLights.render();
		}

	}

	//=========================================================================================================================
	public void setLetterbox(boolean on, int slideDurationTicks, int size)
	{//=========================================================================================================================
		if(on==true)
		{
			letterbox.setOn(slideDurationTicks, size);
		}
		else
		{
			letterbox.setOff(slideDurationTicks);
		}
	}
	//=========================================================================================================================
	public void setLetterbox(boolean on, int slideDurationTicks, float sizePercent)
	{//=========================================================================================================================
		if(on==true)
		{
			letterbox.setOn(slideDurationTicks, sizePercent);
		}
		else
		{
			letterbox.setOff(slideDurationTicks);
		}
	}

	//=========================================================================================================================
	public void fadeToWhite(int ticks)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(BobColor.white,0.0f,1.0f,ticks);
	}
	//=========================================================================================================================
	public void fadeFromWhite(int ticks)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(BobColor.white,1.0f,0.0f,ticks);
	}

	//=========================================================================================================================
	public void fadeToBlack(int ticks)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(BobColor.black,0.0f,1.0f,ticks);
	}
	//=========================================================================================================================
	public void fadeFromBlack(int ticks)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(BobColor.black,1.0f,0.0f,ticks);
	}



//	//=========================================================================================================================
//	public void fadeColorFromCurrentAlphaToOpaque(int ticks, int ri, int gi, int bi)
//	{//=========================================================================================================================
//		screenOverlay.doTransition(new BobColor(ri,gi,bi),-1,1.0f,ticks);
//	}
//	//=========================================================================================================================
//	public void fadeColorFromOpaqueToTransparent(int ticks, int ri, int gi, int bi)
//	{//=========================================================================================================================
//		screenOverlay.doTransition(new BobColor(ri,gi,bi),1.0f,0.0f,ticks);
//	}

	//=========================================================================================================================
	public void fadeColorFromCurrentAlphaToAlpha(int ticks, int ri, int gi, int bi, float toAlpha)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(new BobColor(ri,gi,bi),-1,toAlpha,ticks);
	}
	//=========================================================================================================================
	public void fadeColorFromAlphaToAlpha(int ticks, int ri, int gi, int bi, float fromAlpha, float toAlpha)
	{//=========================================================================================================================
		screenOverlayOverLights.doTransition(new BobColor(ri,gi,bi),fromAlpha,toAlpha,ticks);
	}

//	//=========================================================================================================================
//	public void fadeFromTransparentToBlackOpaqueAndBackToTransparent(int ticks)
//	{//=========================================================================================================================
//		screenOverlay.doToAndFromTransition(BobColor.black,ticks, 1.0f);
//	}
//
//	//=========================================================================================================================
//	public void fadeFromTransparentToWhiteOpaqueAndBackToTransparent(int ticks)
//	{//=========================================================================================================================
//		screenOverlay.doToAndFromTransition(BobColor.white,ticks,1.0f);
//	}

//	//=========================================================================================================================
//	public void fadeColorFromTransparentToOpaqueAndBack(int ticks, int ri, int gi, int bi)
//	{//=========================================================================================================================
//		screenOverlay.doToAndFromTransition(new BobColor(ri,gi,bi),ticks,1.0f);
//	}
	//=========================================================================================================================
	public void fadeColorFromTransparentToAlphaBackToTransparent(int ticks, int ri, int gi, int bi, float toAlpha)
	{//=========================================================================================================================
		screenOverlayOverLights.doToAndFromTransition(new BobColor(ri,gi,bi),ticks, toAlpha);
	}
//	//=========================================================================================================================
//	public void fadeColorFromCurrentAlphaToAlphaBackToCurrentAlpha(int ticks, int ri, int gi, int bi, float toAlpha)
//	{//=========================================================================================================================
//		screenOverlay.doToAndFromTransition(new BobColor(ri,gi,bi),ticks, toAlpha);
//	}
	//=========================================================================================================================
	public void setInstantOverlayColor(int ri,int gi, int bi, float a)
	{//=========================================================================================================================
		screenOverlayOverLights.setInstantOverlay(new BobColor(ri,gi,bi),a);
	}

	//=========================================================================================================================
	public void clearOverlay()
	{//=========================================================================================================================
		screenOverlayOverLights.clearOverlays();
	}

	//TODO eventually redo overlay system to make disposable events that i can combine, i.e. flash red while fading to black, etc.





	//=========================================================================================================================
	public void fadeColorFromCurrentAlphaToAlphaUnderLights(int ticks, int ri, int gi, int bi, float toAlpha)
	{//=========================================================================================================================
		screenOverlayUnderLights.doTransition(new BobColor(ri,gi,bi),-1,toAlpha,ticks);
	}

	//=========================================================================================================================
	public void setInstantOverlayColorUnderLights(int ri,int gi, int bi, float a)
	{//=========================================================================================================================
		screenOverlayUnderLights.setInstantOverlay(new BobColor(ri,gi,bi),a);
	}

	//=========================================================================================================================
	public void clearOverlayUnderLights()
	{//=========================================================================================================================
		screenOverlayUnderLights.clearOverlays();
	}


	//=========================================================================================================================
	public void fadeColorFromCurrentAlphaToAlphaGroundLayer(int ticks, int ri, int gi, int bi, float toAlpha)
	{//=========================================================================================================================
		screenOverlayGroundLayer.doTransition(new BobColor(ri,gi,bi),-1,toAlpha,ticks);
	}

	//=========================================================================================================================
	public void setInstantOverlayColorGroundLayer(int ri,int gi, int bi, float a)
	{//=========================================================================================================================
		screenOverlayGroundLayer.setInstantOverlay(new BobColor(ri,gi,bi),a);
	}

	//=========================================================================================================================
	public void clearOverlayGroundLayer()
	{//=========================================================================================================================
		screenOverlayGroundLayer.clearOverlays();
	}

	//=========================================================================================================================
	public void set8BitMode(boolean b)
	{//=========================================================================================================================
		MapManager().effects8Bit = b;

	}

	//=========================================================================================================================
	public void setInvertedColors(boolean b)
	{//=========================================================================================================================
		MapManager().effectsInverted = b;

	}

	//=========================================================================================================================
	public void setBlackAndWhite(boolean b)
	{//=========================================================================================================================
		MapManager().effectsBlackAndWhite = b;

	}

	//=========================================================================================================================
	public void setRotate(boolean b)
	{//=========================================================================================================================

		//rotate in a "swing" fashion, back and forth
		//MapManager().swingBackAndForth(ticksDuration, maxDegrees, ticksBetweenSwing);

		//rotate in a spiral
		//MapManager().rotateInSpiral(ticksDuration, maxDegrees, ticksBetweenSwing);
	}

	//=========================================================================================================================
	public void setHBlankWave(boolean b)
	{//=========================================================================================================================
		//do this with an FBO

	}

	//=========================================================================================================================
	public void setMosaic(boolean b)
	{//=========================================================================================================================

		//MapManager().mosaicEffect(ticksDuration, maxMosaicSize);

		//TODO: make event for this
	}

	//=========================================================================================================================
	public void setBlur(boolean b)
	{//=========================================================================================================================

		//MapManager().blurEffect(ticksDuration,maxBlurStrength);

		//TODO: make event for this

		//blur on/off
		//blur DURATION
	}

	//=========================================================================================================================
	public void openEyes(int ticksDuration)
	{//=========================================================================================================================
		//blur and letterbox

		//TODO: make event for this
	}
	//=========================================================================================================================
	public void closeEyes(int ticksDuration)
	{//=========================================================================================================================
		//blur and letterbox

		//TODO: make event for this
	}

	//=========================================================================================================================
	public void shakeScreenForTicksDurationEaseInAndOutToMaxAmountWithEasingBetweenShakes(int ticksDuration, int maxX, int maxY, int ticksPerShake)
	{//=========================================================================================================================
		Cameraman().setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

	}

	//=========================================================================================================================
	public void shakeScreenForTicksDurationConstantRateEasingBetweenShakes(boolean onOff, int maxX, int maxY, int ticksPerShake)
	{//=========================================================================================================================
		//Cameraman().setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

		//TODO: make event for this

	}

	//=========================================================================================================================
	public void shakeScreenOnOffConstantRateEasingBetweenShakesMustTurnOff(boolean onOff, int maxX, int maxY, int ticksPerShake)
	{//=========================================================================================================================
		//Cameraman().setShakeScreen(ticksDuration,maxX,maxY,ticksPerShake);

		//TODO: make event for this

	}

	//=========================================================================================================================
	public void setGameSpeed(float multiplier)
	{//=========================================================================================================================

		//TODO: make event for this


	}






}
