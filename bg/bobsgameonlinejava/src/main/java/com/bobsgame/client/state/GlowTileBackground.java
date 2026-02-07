package com.bobsgame.client.state;
import com.bobsgame.client.LWJGLUtils;

import java.util.ArrayList;


import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.game.gui.MenuPanel;
import com.bobsgame.shared.Utils;


//=========================================================================================================================
public class GlowTileBackground extends MenuPanel
{//=========================================================================================================================


	Engine g;

	//=========================================================================================================================
	public class GlowTile
	{//=========================================================================================================================
		public int tileX=0;
		public int tileY=0;
		public int frame=0;
		public long ticks=0;//=1000+Utils.randUpToIncluding(5000);
		public boolean started=false;
	}

	public ArrayList<GlowTile> glowTiles = new ArrayList<GlowTile>();
	public Texture[] glowTileFramesTexture;
	public Texture bgScrollTexture;
	public float bgScrollX = 0;
	public float bgScrollY = 0;
	public long ticksPassed=0;





	public int filter = GLUtils.FILTER_LINEAR;


	//must set these in init()
	public int tileFrames;
	public int numActiveTiles;
	public float scale;
	public int ticksPerFrame;
	public float scrollSpeedTicksMultiplier;


	//=========================================================================================================================
	public GlowTileBackground()
	{//=========================================================================================================================
		super();
		init();
	}

	//=========================================================================================================================
	public GlowTileBackground(Engine g)
	{//=========================================================================================================================
		super();
		this.g=g;
		init();
	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		numActiveTiles=4;
		scale = 2.0f;
		ticksPerFrame = 60; // Slower animation
		scrollSpeedTicksMultiplier = (1.0f/100.0f); // Slower scroll

		tileFrames = 115;


		cleanup();

		bgScrollTexture = GLUtils.loadTexture("res/guiBackground/glowTileFramesBG.png");

		glowTileFramesTexture = new Texture[tileFrames];
		for(int i=0;i<tileFrames;i++)
		glowTileFramesTexture[i] = GLUtils.loadTexture("res/guiBackground/glowTileFrames/" +i+".png");

		glowTiles.clear();

		for(int i=0;i<numActiveTiles;i++)
		{
            GlowTile tile = new GlowTile();
            tile.started = true;
            // Space them out initially to avoid delay
            tile.frame = (tileFrames / numActiveTiles) * i;
			glowTiles.add(tile);
		}

	}


	//=========================================================================================================================
	public void cleanup()
	{//=========================================================================================================================
		if(glowTileFramesTexture!=null&&glowTileFramesTexture.length>0)
		{
			for(int i=0;i<glowTileFramesTexture.length;i++)
			{
				if(glowTileFramesTexture[i]!=null)
				glowTileFramesTexture[i] = GLUtils.releaseTexture(glowTileFramesTexture[i]);
			}
			glowTileFramesTexture = null;
		}

		if(bgScrollTexture!=null)bgScrollTexture = GLUtils.releaseTexture(bgScrollTexture);


	}


	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================


		if(glowTileFramesTexture==null)init();

		if(g!=null)ticksPassed=g.engineTicksPassed();
		else
		ticksPassed = Engine.mainTicksPassed;

		float tileWidth = glowTileFramesTexture[0].getImageWidth()*scale;
		float tileHeight = glowTileFramesTexture[0].getImageHeight()*scale;


		int screenWidth = LWJGLUtils.SCREEN_SIZE_X;
		int screenHeight = LWJGLUtils.SCREEN_SIZE_Y;

		if(g!=null)
		{
			screenWidth = (int)g.getWidth();
			screenHeight = (int)g.getHeight();
		}

		//------------------------------------------
		//set the bg glow frames
		//------------------------------------------
			for(int i=0;i<glowTiles.size();i++)
			{
				GlowTile tile = glowTiles.get(i);

				tile.ticks+=ticksPassed;
				if(tile.ticks>ticksPerFrame)
				{
					tile.ticks=0;

					//get the next glowtile
					int next=i+1;
					if(next>=glowTiles.size())next=0;

					GlowTile nextTile = glowTiles.get(next);

					if(tile.started==false)
					{
						//if next is at frame length, set to started.
						if(nextTile.frame>=(tileFrames)/glowTiles.size())tile.started=true;
					}


					if(tile.started==true)
					{
						tile.frame++;
						if(tile.frame>=tileFrames)
						{
							tile.frame=0;

							//follow the previous tile for snake-like movement.
							if(Utils.randLessThan(2)==0)
							{
								tile.tileX=nextTile.tileX;
								tile.tileY=nextTile.tileY+1;
							}//down
							else
							{
								tile.tileX=nextTile.tileX+1;
								tile.tileY=nextTile.tileY;
							}//right


							//wrap around
							if(tile.tileX>screenWidth/tileWidth)tile.tileX=0;
							if(tile.tileX<0)tile.tileX=(int)(screenWidth/tileWidth);

							if(tile.tileY>screenHeight/tileHeight)tile.tileY=0;
							if(tile.tileY<0)tile.tileY=(int)(screenHeight/tileHeight);

							//pick a random tile
							//bg_glow_offset[f][0]=((rand()%13)*32);
							//bg_glow_offset[f][1]=((rand()%11)*32);

							//bg_glow_ticks[f]+=(500+rand()%2000);

						}
					}
				}
			}
		//------------------------------------------

		//------------------------------------------
		//set the bg scrolling
		//------------------------------------------


		bgScrollX-=ticksPassed*scrollSpeedTicksMultiplier;
		bgScrollY-=ticksPassed*scrollSpeedTicksMultiplier;


		if(bgScrollX<=-tileWidth)
		{
			bgScrollX=0;


			//move the glow offsets when the bg loops
			for(int i=0;i<glowTiles.size();i++)
			{
				GlowTile tile = glowTiles.get(i);
				tile.tileX-=1;
				if(tile.tileX<0)tile.tileX+=(int)(screenWidth/tileWidth);

			}
		}

		if(bgScrollY<=-tileHeight)
		{

			bgScrollY=0;

			//move the glow offsets when the bg loops
			for(int i=0;i<glowTiles.size();i++)
			{
				GlowTile tile = glowTiles.get(i);
				tile.tileY-=1;
				if(tile.tileY<0)tile.tileY+=(int)(screenHeight/tileHeight);
			}
		}


		// Fixed: animation is too fast
		// Fixed: weird delay on start



	}





	//=========================================================================================================================
	public void render()
	{//=========================================================================================================================

		//------------------------------------------
		//draw background png
		//------------------------------------------

		//starting at bgScrollXY, draw bgScrollTexture until overlaps screen size x and y
		{
			Texture texture = bgScrollTexture;

			int w = texture.getImageWidth();
			int h = texture.getImageHeight();

			float screenWidth = LWJGLUtils.SCREEN_SIZE_X;
			float screenHeight = LWJGLUtils.SCREEN_SIZE_Y;

			if(g!=null)
			{
				screenWidth = g.getWidth();
				screenHeight = g.getHeight();
			}

			//if the screen is bigger than the background scroll image we need to tile it
			int drawX = (int) (((screenWidth-(bgScrollX))/(w*scale)))+1;
			int drawY = (int) (((screenHeight-(bgScrollY))/(h*scale)))+1;

			for(int y=0;y<drawY;y++)
			for(int x=0;x<drawX;x++)
			{

				float x0 = bgScrollX+(x*w*scale);
				float x1 = x0 + w*scale;
				float y0 = bgScrollY+(y*h*scale);
				float y1 = y0 + h*scale;


				GLUtils.drawTexture(texture,x0,x1,y0,y1,1.0f,filter);
			}
		}

		//------------------------------------------
		//draw background glow
		//------------------------------------------

			for(int i=glowTiles.size()-1;i>=0;i--)//from top to bottom
			{
				GlowTile tile = glowTiles.get(i);


					Texture texture = glowTileFramesTexture[tile.frame];
					int w = texture.getImageWidth();
					int h = texture.getImageHeight();

					float tXRatio = (float)texture.getImageWidth()/(float)texture.getTextureWidth();
					float tYRatio = (float)texture.getImageHeight()/(float)texture.getTextureHeight();

					float x0 = bgScrollX+tile.tileX*w*scale;
					float x1 = x0 + w*scale;
					float y0 = bgScrollY+tile.tileY*h*scale;
					float y1 = y0 + h*scale;

					float tx0 = 0.0f * tXRatio;
					float tx1 = 1.0f * tXRatio;
					float ty0 = 0.0f * tYRatio;
					float ty1 = 1.0f * tYRatio;

					GLUtils.drawTexture(texture,tx0,tx1,ty0,ty1,x0,x1,y0,y1,1.0f,filter);

			}


	}






}
