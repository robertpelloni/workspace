package com.bobsgame.client.engine.game.nd.ndmenu;

import com.bobsgame.client.Texture;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.state.GlowTileBackground;


//=========================================================================================================================
public class NDMenuBackground extends GlowTileBackground
{//=========================================================================================================================

	//=========================================================================================================================
	public NDMenuBackground(Engine g)
	{//=========================================================================================================================
		super(g);
	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================

		numActiveTiles=6;
		scale = 0.75f;
		ticksPerFrame = 20;
		scrollSpeedTicksMultiplier = (1.0f/64.0f);
		filter = GLUtils.FILTER_LINEAR;


		tileFrames = 65;//get from generator tool output


		cleanup();

		bgScrollTexture = GLUtils.loadTexture("res/guiBackground/nDmenuBG.png");

		glowTileFramesTexture = new Texture[tileFrames];
		for(int i=0;i<tileFrames;i++)
		glowTileFramesTexture[i] = GLUtils.loadTexture("res/guiBackground/nDmenu/" +i+".png");

		glowTiles.clear();

		for(int i=0;i<numActiveTiles;i++)
		{
			glowTiles.add(new GlowTile());
		}

		glowTiles.get(0).started=true;
	}


}
