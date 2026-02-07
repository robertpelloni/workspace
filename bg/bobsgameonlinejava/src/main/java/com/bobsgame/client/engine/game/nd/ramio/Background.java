package com.bobsgame.client.engine.game.nd.ramio;

import com.bobsgame.client.engine.map.Map;
import com.bobsgame.shared.MapData;
import com.bobsgame.client.engine.Engine;
//=========================================================================================================================
public class Background extends Map
{//=========================================================================================================================

	//=========================================================================================================================
	public Background(Engine g)
	{//=========================================================================================================================
		
		super(g,new MapData(-1,"ramio",400,20));
	}
	

	public int RAMIO_screen_x = 0;
	public int RAMIO_screen_y = 0;

	public int RAMIO_tv_rolling=0;

	public int RAMIO_scrollingplayingfield_map_x=0;
	public int RAMIO_scrollingplayingfield_map_y=0;
	public int RAMIO_playing_field_map_scroll_x=0;


	public int RAMIO_map_x=0;
	public int RAMIO_offset_x=0;


	public int RAMIO_map_width=0;


	public int RAMIO_tileset_size = 0;

	public int dir=0;
	
	boolean fadeInOutPulseToggle=false;


	//=========================================================================================================================
	void RAMIO_shakeplayingfield()
	{//=========================================================================================================================
		//called every VBL to make the background pretty

	
		if(dir==0)
		{
			RAMIO_playing_field_map_scroll_x++;
			if(RAMIO_playing_field_map_scroll_x>3)
			{
				dir=1;
				RAMIO_playing_field_map_scroll_x--;
			}
		}
		else
		{
			RAMIO_playing_field_map_scroll_x--;
			if(RAMIO_playing_field_map_scroll_x<-3)
			{
				dir=0;
				RAMIO_playing_field_map_scroll_x++;
			}
		}


		//HARDWARE_set_AUX_map_xy(2,TV_fromx+RAMIO_playing_field_map_scroll_x,TV_fromy);
	}


	//=========================================================================================================================
	public void init()
	{//=========================================================================================================================	
		

	}
	
	
	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		super.update();
		
		//if(ticks%3==0)
		{
			// make the tv scanlines pulse
			if(fadeInOutPulseToggle==false)
			{
				fadeInOutPulseToggle=true;
			}
			else
			{
				fadeInOutPulseToggle=false;
			}
		}	
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
