package com.bobsgame.client.engine.game;
import com.bobsgame.client.LWJGLUtils;


import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;

import easing.Easing;


public class EasingTest extends EnginePart
{

	static Caption linearTweenCaption = null;

	static Caption easeInQuadCaption = null;
	static Caption easeInCubicCaption =null;
	static Caption easeInQuartCaption =null;
	static Caption easeInQuintCaption =null;
	static Caption easeInExpoCaption = null;
	static Caption easeInCircCaption = null;
	static Caption easeInSineCaption = null;

	static Caption easeOutQuadCaption =null;
	static Caption easeOutCubicCaption =null;
	static Caption easeOutQuartCaption =null;
	static Caption easeOutQuintCaption =null;
	static Caption easeOutExpoCaption =null;
	static Caption easeOutCircCaption =null;
	static Caption easeOutSineCaption =null;

	static Caption easeInOutQuadCaption =null;
	static Caption easeInOutCubicCaption =null;
	static Caption easeInOutQuartCaption =null;
	static Caption easeInOutQuintCaption =null;
	static Caption easeInOutExpoCaption =null;
	static Caption easeInOutCircCaption =null;
	static Caption easeInOutSineCaption =null;


	public EasingTest(Engine g)
	{
		super(g);

		linearTweenCaption = CaptionManager().newManagedCaption(0, 20*2, -1, "linear", BobFont.font_small_8_outlined, BobColor.WHITE, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);

		easeInQuadCaption = CaptionManager().newManagedCaption(0, 20*3, -1, "x^2", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInCubicCaption = CaptionManager().newManagedCaption(0, 20*4, -1, "x^3", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInQuartCaption = CaptionManager().newManagedCaption(0, 20*5, -1, "x^4", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInQuintCaption = CaptionManager().newManagedCaption(0, 20*6, -1, "x^5", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInExpoCaption = CaptionManager().newManagedCaption(0, 20*7, -1, "2^x", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInCircCaption = CaptionManager().newManagedCaption(0, 20*8, -1, "sqrt(1-x^2)", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInSineCaption = CaptionManager().newManagedCaption(0, 20*9, -1, "sin(x)", BobFont.font_small_8_outlined, BobColor.RED, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);

		easeOutQuadCaption = CaptionManager().newManagedCaption(0, 20*12, -1, "x^2", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutCubicCaption = CaptionManager().newManagedCaption(0, 20*13, -1, "x^3", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutQuartCaption = CaptionManager().newManagedCaption(0, 20*14, -1, "x^4", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutQuintCaption = CaptionManager().newManagedCaption(0, 20*15, -1, "x^5", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutExpoCaption = CaptionManager().newManagedCaption(0, 20*16, -1, "2^x", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutCircCaption = CaptionManager().newManagedCaption(0, 20*17, -1, "sqrt(1-x^2)", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeOutSineCaption = CaptionManager().newManagedCaption(0, 20*18, -1, "sin(x)", BobFont.font_small_8_outlined, BobColor.GREEN, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);

		easeInOutQuadCaption = CaptionManager().newManagedCaption(0, 20*21, -1, "^2", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutCubicCaption = CaptionManager().newManagedCaption(0, 20*22, -1, "^3", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutQuartCaption = CaptionManager().newManagedCaption(0, 20*23, -1, "^4", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutQuintCaption = CaptionManager().newManagedCaption(0, 20*24, -1, "^5", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutExpoCaption = CaptionManager().newManagedCaption(0, 20*25, -1, "2^x", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutCircCaption = CaptionManager().newManagedCaption(0, 20*26, -1, "sqrt(1-x^2)", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);
		easeInOutSineCaption = CaptionManager().newManagedCaption(0, 20*27, -1, "sin(x)", BobFont.font_small_8_outlined, BobColor.YELLOW, BobColor.BLACK, RenderOrder.OVER_GUI, 1.0f, 0);






	}


	static float ticksCount = 0;
	static float duration = 2000;
	static float beginningValue = 100;
	static float changeInValue = LWJGLUtils.SCREEN_SIZE_X-200;

	public void update()
	{

		changeInValue = LWJGLUtils.SCREEN_SIZE_X-200;

		ticksCount+=Engine().engineTicksPassed();
		if(ticksCount>duration)
		{
			ticksCount=0;

			if(changeInValue>0)
			{
				changeInValue*=-1;
				beginningValue=LWJGLUtils.SCREEN_SIZE_X-100;
			}
			else
			{
				changeInValue*=-1;
				beginningValue=100;
			}
		}


		linearTweenCaption.screenX = (float)Easing.linearTween(ticksCount,beginningValue,changeInValue,duration);

		easeInQuadCaption.screenX = (float)Easing.easeInQuadratic(ticksCount,beginningValue,changeInValue,duration);
		easeOutQuadCaption.screenX = (float)Easing.easeOutQuadratic(ticksCount,beginningValue,changeInValue,duration);
		easeInOutQuadCaption.screenX = (float)Easing.easeInOutQuadratic(ticksCount,beginningValue,changeInValue,duration);

		easeInCubicCaption.screenX = (float)Easing.easeInCubic(ticksCount,beginningValue,changeInValue,duration);
		easeOutCubicCaption.screenX = (float)Easing.easeOutCubic(ticksCount,beginningValue,changeInValue,duration);
		easeInOutCubicCaption.screenX = (float)Easing.easeInOutCubic(ticksCount,beginningValue,changeInValue,duration);

		easeInQuartCaption.screenX = (float)Easing.easeInQuartic(ticksCount,beginningValue,changeInValue,duration);
		easeOutQuartCaption.screenX = (float)Easing.easeOutQuartic(ticksCount,beginningValue,changeInValue,duration);
		easeInOutQuartCaption.screenX = (float)Easing.easeInOutQuartic(ticksCount,beginningValue,changeInValue,duration);

		easeInQuintCaption.screenX = (float)Easing.easeInQuintic(ticksCount,beginningValue,changeInValue,duration);
		easeOutQuintCaption.screenX = (float)Easing.easeOutQuintic(ticksCount,beginningValue,changeInValue,duration);
		easeInOutQuintCaption.screenX = (float)Easing.easeInOutQuintic(ticksCount,beginningValue,changeInValue,duration);


		easeInSineCaption.screenX = (float)Easing.easeInSinusoidal(ticksCount,beginningValue,changeInValue,duration);
		easeOutSineCaption.screenX = (float)Easing.easeOutSinusoidal(ticksCount,beginningValue,changeInValue,duration);
		easeInOutSineCaption.screenX = (float)Easing.easeInOutSinusoidal(ticksCount,beginningValue,changeInValue,duration);


		easeInExpoCaption.screenX = (float)Easing.easeInExponential(ticksCount,beginningValue,changeInValue,duration);
		easeOutExpoCaption.screenX = (float)Easing.easeOutExponential(ticksCount,beginningValue,changeInValue,duration);
		easeInOutExpoCaption.screenX = (float)Easing.easeInOutExponential(ticksCount,beginningValue,changeInValue,duration);

		easeInCircCaption.screenX = (float)Easing.easeInCircular(ticksCount,beginningValue,changeInValue,duration);
		easeOutCircCaption.screenX = (float)Easing.easeOutCircular(ticksCount,beginningValue,changeInValue,duration);
		easeInOutCircCaption.screenX = (float)Easing.easeInOutCircular(ticksCount,beginningValue,changeInValue,duration);



	}



}
