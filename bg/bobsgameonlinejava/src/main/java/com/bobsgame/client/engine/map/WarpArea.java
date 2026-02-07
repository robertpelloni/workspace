package com.bobsgame.client.engine.map;

import com.bobsgame.client.GLUtils;
import com.bobsgame.client.engine.Engine;
import com.bobsgame.client.engine.event.Event;
import com.bobsgame.shared.AreaData;
import com.bobsgame.shared.BobColor;


//=========================================================================================================================
public class WarpArea extends Area
{//=========================================================================================================================


	//WarpArea: MapAsset this, String name, int mapXPixels (1x), int mapYPixels (1x), int widthPixels (1x), int heightPixels (1x), String destination, int arrivalXPixels (1x), int arrivalYPixels (1x)




	//=========================================================================================================================
	public WarpArea(Engine g, AreaData a)
	{//=========================================================================================================================

		super(g);

		this.data = a;

		this.mapX = a.mapXPixelsHQ();
		this.mapY = a.mapYPixelsHQ();

		if(eventData()!=null)
		{
			Event event = EventManager().getEventByIDCreateIfNotExist(eventData().id());
			event.area = this;
		}

	}





	public long lastRequestedMapDataTime = 0;

	//=========================================================================================================================
	public void update()
	{//=========================================================================================================================
		super.update();

		long time = System.currentTimeMillis();
		if(time-lastRequestedMapDataTime>5000)
		{
			lastRequestedMapDataTime = time;

			if(destinationMapName().length()>0)
				MapManager().requestMapDataIfNotLoadedYet(destinationMapName());
		}

	}



	//=========================================================================================================================
	public void enter()
	{//=========================================================================================================================

		//go through mapMan().doorList and find door.mapAsset=destinationMapAsset and door.entityNameIdentifier=destinationDoorName, get arrival x and arrival y

		if(destinationTYPEIDString()==null||destinationTYPEIDString().length()==0||destinationTYPEIDString().equals("AREA."+id()))return;


			Map map = MapManager().getMapByNameBlockUntilLoaded(destinationMapName());

			if(map!=null)
			{
				for(int i=0; i<map.warpAreaList.size();i++)
				{
					WarpArea w = map.warpAreaList.get(i);


					//if(w.mapAsset==MapManager().getMapByName(destinationMapName()))//should always be true since we are checking the destination map above
					//{

						if(w.name().equals(destinationWarpAreaName()))
						{

							MapManager().warpEntered = this;
							MapManager().warpExited = w;



							float arrivalX = w.arrivalXPixelsHQ();
							float arrivalY = w.arrivalYPixelsHQ();


							//keep horizontal position in between warpareas and doors.

							//if this is wider than tall, keep x position and use arrivalY

							if(w()>h())
							{
								arrivalX = w.x() + (Player().x() - x()) + Player().w()/2;
							}

							if(h()>w())
							{
								arrivalY = w.y() + (Player().y() - y()) + Player().h()/2;
							}


							MapManager().changeMap(destinationMapName(),(int)(arrivalX)+8,(int)(arrivalY)+8);
							return;
						}
					//}
				}
			}




	}
	//=========================================================================================================================
	public void renderDebugInfo()
	{//=========================================================================================================================


		int x = (int)screenLeft();
		int y = (int)screenTop();
		GLUtils.drawOutlinedString(name(), x, y-36,BobColor.white);


		GLUtils.drawOutlinedString("destinationTYPEIDString: "+destinationTYPEIDString(), x, y-27,new BobColor(200,0,255));

		if(
				destinationTYPEIDString().equals("AREA."+id())
				||
				destinationTYPEIDString().equals("")
				||
				destinationTYPEIDString().equals("none")
				||
				destinationTYPEIDString().equals("self")

		)//if it doesn't have a destination set, mark it as problematic
		GLUtils.drawOutlinedString("WarpArea: Has no destination!", x, y-18,BobColor.red);
		//else
		GLUtils.drawOutlinedString("WarpArea: Goes to Map.Name: "+destinationMapName()+"."+destinationWarpAreaName(), x, y-9,new BobColor(200,0,255,255));






		super.renderDebugInfo();

	}


	public void setDestinationTYPEIDString(String typeID){getData().setDestinationTYPEIDString(typeID);}

	public String destinationMapName(){return getData().destinationMapName();}
	public String destinationWarpAreaName(){return getData().destinationWarpAreaName();}




}
