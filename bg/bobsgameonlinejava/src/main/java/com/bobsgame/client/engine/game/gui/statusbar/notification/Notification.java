package com.bobsgame.client.engine.game.gui.statusbar.notification;

import com.bobsgame.client.LWJGLUtils;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.game.ClientGameEngine;
import com.bobsgame.client.engine.game.gui.statusbar.NotificationManager;
import com.bobsgame.client.engine.game.gui.statusbar.buttons.StatusBarButton;
import com.bobsgame.client.engine.text.Caption;
import com.bobsgame.shared.BobColor;
import com.bobsgame.shared.MapData.RenderOrder;
import com.bobsgame.client.engine.text.BobFont;



//=========================================================================================================================
public class Notification extends StatusBarButton
{//=========================================================================================================================



	public Caption caption;


	public String string;

	public boolean fadeIn=false;
	public boolean fadeOut=false;


	public float progress = 0;
	public float lastProgress = 0;
	public int progressBarFrame = 0;
	public boolean hasProgressBar = true;
	public int progressTicks = 0;
	public int lastProgressTicks = 0;

	public float alpha = 0.0f;


	public float scrollX = 0;
	public boolean scrolling = false;



	//=========================================================================================================================
	public Notification(ClientGameEngine g, String s)
	{//=========================================================================================================================

		super(g);

		string = s;



		/*
		 *
		 *
		 *
		 * notifications when entering area: "loading area" with progress bar.
		 *
		 * new game available in game store!
		 *
		 *
		 *
		 * your friend is online!
		 *
		 *
		 *
		 *
		*/

		if(caption==null)
		{
			caption=new Caption(g,0,5,-1,string,BobFont.font_normal_11_shadow1,BobColor.PURPLE,BobColor.WHITE,BobColor.CLEAR,RenderOrder.OVER_GUI,1.0f,LWJGLUtils.SCREEN_SIZE_X);
			caption.setAlphaImmediately(1.0f);
		}


		fadeIn=true;



		StatusBar().notificationManager.add(this);



	}



	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		if(caption==null)
		{
			caption=new Caption(Engine(),0,5,-1,string,BobFont.font_normal_11_shadow1,BobColor.PURPLE,BobColor.WHITE,BobColor.CLEAR,RenderOrder.OVER_GUI,1.0f,LWJGLUtils.SCREEN_SIZE_X);
			caption.setAlphaImmediately(1.0f);
		}


		if(fadeIn==true)
		{
			if(alpha<1.0f)alpha+=Engine().engineTicksPassed()*0.001;
			if(alpha>1.0f)alpha=1.0f;
		}



		if(fadeOut==true)
		{
			fadeIn=false;

			if(alpha>0.0f)alpha-=Engine().engineTicksPassed()*0.001;
			if(alpha<0.0f)alpha=0.0f;

			if(alpha==0.0f)
			{
				StatusBar().notificationManager.remove(this);


				if(caption.texture!=null)
				{
					//caption.texture.release();
					caption.texture=GLUtils.releaseTexture(caption.texture);
				}
				caption.textureByteBuffer = null;
				caption.textureByteArray = null;

				caption = null;

				return;
			}
		}






		float maxWidth = (LWJGLUtils.SCREEN_SIZE_X-caption.screenX)-(LWJGLUtils.SCREEN_SIZE_X-(StatusBar().moneyCaption.dividerX));

		if(scrolling==false&&maxWidth<caption.texture.getImageWidth())
		{
			scrolling=true;
			scrollX = maxWidth;
			caption.screenX=StatusBar().stuffButton.dividerX+3;//we want to scroll right up to the divider
		}
		//else scrolling=false;

		if(scrolling==true)
		{
			scrollX-=Engine().engineTicksPassed()*0.08;
			if(scrollX<0-caption.texture.getImageWidth())scrollX=maxWidth;

		}
		else
		{
			caption.screenX=StatusBar().stuffButton.dividerX+3+10;//we want to stay 10 pixels away from the divider
		}


		if(hasProgressBar==true)
		{
			//progress+=Game().ticksPassed()*0.0f001;
			if(progress<0.0f)progress=0.0f;
			if(progress>1.0f)progress=1.0f;


			progressTicks+=Engine().engineTicksPassed();

			if(lastProgressTicks+5<progressTicks&&progress<1.0f)
			{
				lastProgressTicks=progressTicks;
				//progressBarFrame++;
				//if(progressBarFrame>15)progressBarFrame=0;
			}

		}



	}

	//=========================================================================================================================
	public void render(int layer)
	{//=========================================================================================================================

		if(layer==0)
		{


			float screenX = StatusBar().stuffButton.dividerX+3;
			float maxWidth = (LWJGLUtils.SCREEN_SIZE_X-screenX)-(LWJGLUtils.SCREEN_SIZE_X-(StatusBar().moneyCaption.dividerX));


			if(hasProgressBar==true)
			{
				//render progress bar



				/*
				Texture bg = NotificationManager.loadingBarBackgroundTexture;
				float bgw = bg.getImageWidth();
				float bgh = bg.getImageHeight();
				float bgtx1 = bgw/(float)bg.getTextureWidth();
				float bgty1 = bgh/(float)bg.getTextureHeight();
				GL.drawTexture(bg,0,bgtx1,0,bgty1,screenX,screenX+maxWidth,0,25,1.0f,1);*/


				Texture fg = NotificationManager.loadingBarTexture;
				float fgImageWidth = fg.getImageWidth();
				float fgTextureWidth = fg.getTextureWidth();
				float fgImageHeight = fg.getImageHeight();
				float fgTextureHeight = fg.getTextureHeight();
				float fgFrameHeight = fgImageHeight;///16.0f;

				float fgtx0 = 0;
				float fgtx1 = (progress*fgImageWidth)/fgTextureWidth;

				float fgty0 = (progressBarFrame*fgFrameHeight)/fgTextureHeight;
				float fgty1 = ((progressBarFrame+1)*fgFrameHeight)/fgTextureHeight;

				float fgx1 = progress*maxWidth;

				GLUtils.drawTexture(fg,fgtx0,fgtx1,fgty0,fgty1,screenX,screenX+fgx1,0,25,alpha*0.75f,1);

			}


			if(caption!=null)
			{
				float tx0 = 0.0f;
				float tx1 = (float)caption.texture.getImageWidth()/(float)caption.texture.getTextureWidth();
				float ty0 = 0.0f;
				float ty1 = (float)caption.texture.getImageHeight()/(float)caption.texture.getTextureHeight();

				float x0 = (caption.screenX);
				float x1 = (caption.screenX+caption.texture.getImageWidth());
				float y0 = (caption.screenY);
				float y1 = (caption.screenY+caption.texture.getImageHeight());


				//notifications scrolling back and forth



				if(scrolling==true)
				{


					//figure out where x0 should be based on scrollX

					if(scrollX<0)
					{
						//x0 is 0, set x texture clip

						x0 = caption.screenX;
						tx0 = (0-scrollX)/(float)caption.texture.getTextureWidth();

						//if the rest will fit
						if(scrollX+caption.texture.getImageWidth()<maxWidth)
						{
							tx1 = (float)caption.texture.getImageWidth()/(float)caption.texture.getTextureWidth();
							x1 = caption.screenX + scrollX+caption.texture.getImageWidth();
						}
						else
						{
							//clip x1 and tx1

							tx1 = ((0-scrollX)+maxWidth)/(float)caption.texture.getTextureWidth();
							x1 = caption.screenX + maxWidth;

						}
					}
					else
					{
						x0 = caption.screenX+scrollX;
						tx0 = 0.0f;

						//if it is scrolling off the end
						if(scrollX + caption.texture.getImageWidth() > maxWidth)
						{
							//clip it
							x1 = x0 + (maxWidth-scrollX);
							tx1 = (maxWidth-scrollX)/(float)caption.texture.getTextureWidth();

						}
						else
						{
							//draw the whole thing
							x1 = x0 + caption.texture.getImageWidth();
							tx1 = (float)caption.texture.getImageWidth()/(float)caption.texture.getTextureWidth();

						}


					}



				}
				else
				{

					x0 = (caption.screenX);
					x1 = (caption.screenX+caption.texture.getImageWidth());
					y0 = (caption.screenY);
					y1 = (caption.screenY+caption.texture.getImageHeight());
				}







				GLUtils.drawTexture(caption.texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,alpha,GLUtils.FILTER_FBO_NEAREST_NO_MIPMAPPING);

			}
		}

	}



	public Notification delete()
	{

		fadeOut=true;



		return null;
	}
}