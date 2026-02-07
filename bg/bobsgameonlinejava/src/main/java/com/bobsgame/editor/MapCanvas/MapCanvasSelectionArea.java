package com.bobsgame.editor.MapCanvas;

import java.awt.Color;
import java.util.ArrayList;

import com.bobsgame.EditorMain;
import com.bobsgame.editor.SelectionArea;
import com.bobsgame.editor.Project.Project;
import com.bobsgame.editor.Project.Map.Area;
import com.bobsgame.editor.Project.Map.Door;
import com.bobsgame.editor.Project.Map.Entity;
import com.bobsgame.editor.Project.Map.Light;
import com.bobsgame.editor.Project.Map.Map;
import com.bobsgame.editor.Project.Map.MapState;
import com.bobsgame.shared.MapData;
import com.bobsgame.editor.Undo.*;
//import javax.swing.undo.*;

//===============================================================================================
public class MapCanvasSelectionArea extends SelectionArea
{//===============================================================================================
	private MapCanvas MC;


	public boolean isSelectedLock = false;
	public boolean isShowingLock = false;

	public int x1Lock, y1Lock, x2Lock, y2Lock;

	public ArrayList<Entity> copyEntityList = new ArrayList<Entity>();
	public ArrayList<Area> copyAreaList = new ArrayList<Area>();
	public ArrayList<Light> copyLightList = new ArrayList<Light>();
	public ArrayList<Door> copyDoorList = new ArrayList<Door>();

	public int copyX = 0;//used for calculating the offset from the copy position to the paste position
	public int copyY = 0;
	public boolean cutObjects = false; //used to decide whether to delete the original objects
	public boolean copiedObjects = false;
	public Map copyMap = null; //if this is the same as the paste map, don't delete the connections.

	//===============================================================================================
	public MapCanvasSelectionArea(MapCanvas mc)
	{//===============================================================================================
		super();
		MC = mc;
		//type = MAP_TYPE;
		setBackground(new Color(255, 255, 255, 50));//bob 20060624
	}


	//===============================================================================================
	public void setVisibleLock(boolean b)
	{//===============================================================================================
		isShowingLock = b;

	}


	//===============================================================================================
	public boolean isShowingLock()
	{//===============================================================================================
		return isShowingLock;
	}


	//===============================================================================================
	public void setLocationLock(int x, int y)
	{//===============================================================================================
		boolean temp = isShowingLock;
		if(temp)
		{
			setVisibleLock(false);
		}

		x1Lock = x;
		y1Lock = y;
		if(temp)
		{
			setVisibleLock(true);
		}


	}

	//===============================================================================================
	public void setLocation2Lock(int x, int y)
	{//===============================================================================================
		boolean temp = isShowingLock;
		if(temp)
		{
			setVisibleLock(false);
		}
		x2Lock = x;
		y2Lock = y;
		if(temp)
		{
			setVisibleLock(true);
		}

	}


	//===============================================================================================
	public void setSizeLock(int x, int y)
	{//===============================================================================================
		boolean temp = isShowing;
		if(temp)
		{
			setVisibleLock(false);
		}
		x2Lock = x1Lock + x;
		y2Lock = y1Lock + y;
		if(temp)
		{
			setVisibleLock(true);
		}
	}

	//===============================================================================================
	public void cutObjects()
	{//===============================================================================================




		if(isCopiedOrCut!=true)return;

		if(MapCanvas.selectedAllLayers!=true)return;

		//make temp linked list of doors, areas, lights, entities under the selection
		copyEntityList.clear();
		copyLightList.clear();
		copyDoorList.clear();
		copyAreaList.clear();


		Map m = MC.getMap();

		m.setSelectedAreaIndex(-1);
		m.setSelectedDoorIndex(-1);
		m.setSelectedLightIndex(-1);
		m.setSelectedEntityIndex(-1);

		copyX = x1;
		copyY = y1;
		copyMap = m;
		//used for calculating the offset from the copy position to the paste position

		copiedObjects=false;
		cutObjects = true;

		//move lights, doors, sprites, actions



		for(int i=0;i<m.getNumAreas();i++)
		{
			Area area = m.getArea(i);
			if(
					contains(area.xP()/8,area.yP()/8)||
					contains((area.xP())/8,(area.yP()+area.hP()-1)/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP())/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP()+area.hP()-1)/8)
			)
			{
				copyAreaList.add(area);
				m.removeArea(i);
				i=-1;

			}

		}

		for(int i=0;i<m.getNumDoors();i++)
		{

			Door door = m.getDoor(i);

			if(
					contains(door.xP()/8,door.yP()/8)||
					contains((door.xP())/8,(door.yP()+door.hP()-1)/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP())/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP()+door.hP()-1)/8)
			)
			{
				copyDoorList.add(door);
				m.removeDoor(door);
				i=-1;
			}

		}

		for(int i=0;i<m.getNumEntities();i++)
		{
			Entity entity = m.getEntity(i);

			if(
					contains(entity.xP()/8,entity.yP()/8)||
					contains((entity.xP())/8,(entity.yP()+(int)((entity.hP()-1)))/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(entity.yP())/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(int)(entity.yP()+((entity.hP()-1)))/8)
			)
			{
				copyEntityList.add(entity);
				m.removeEntity(i);
				i=-1;
			}
		}

		for(int i=0;i<m.getNumLights();i++)
		{
			Light light = m.getLight(i);

			if(
					contains(light.xP()/8,light.yP()/8)||
					contains((light.xP())/8,(light.yP()+light.hP()-1)/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP())/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP()+light.hP()-1)/8)
			)
			{
				copyLightList.add(light);
				m.removeLight(i);
				i=-1;
			}
		}



	}

	//===============================================================================================
	public void copyObjects()
	{//===============================================================================================
		if(MapCanvas.selectedAllLayers!=true)return;

		//make temp linked list of doors, areas, lights, entities under the selection
		copyEntityList.clear();
		copyLightList.clear();
		copyDoorList.clear();
		copyAreaList.clear();


		Map m = MC.getMap();

		m.setSelectedAreaIndex(-1);
		m.setSelectedDoorIndex(-1);
		m.setSelectedLightIndex(-1);
		m.setSelectedEntityIndex(-1);

		copyX = x1;
		copyY = y1;
		//used for calculating the offset from the copy position to the paste position

		copiedObjects=true;
		cutObjects = false;

		copyMap = m;

		//move lights, doors, sprites, actions



		for(int i=0;i<m.getNumAreas();i++)
		{
			Area area = m.getArea(i);
			if(
					contains(area.xP()/8,area.yP()/8)||
					contains((area.xP())/8,(area.yP()+area.hP()-1)/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP())/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP()+area.hP()-1)/8)
			)
			{
				copyAreaList.add(area);
			}

		}

		for(int i=0;i<m.getNumDoors();i++)
		{

			Door door = m.getDoor(i);

			if(
					contains(door.xP()/8,door.yP()/8)||
					contains((door.xP())/8,(door.yP()+door.hP()-1)/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP())/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP()+door.hP()-1)/8)
			)
			{
				copyDoorList.add(door);
			}

		}

		for(int i=0;i<m.getNumEntities();i++)
		{
			Entity entity = m.getEntity(i);

			if(
					contains(entity.xP()/8,entity.yP()/8)||
					contains((entity.xP())/8,(entity.yP()+(int)((entity.hP()-1)))/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(entity.yP())/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(int)(entity.yP()+((entity.hP()-1)))/8)
			)
			{
				copyEntityList.add(entity);
			}
		}

		for(int i=0;i<m.getNumLights();i++)
		{
			Light light = m.getLight(i);

			if(
					contains(light.xP()/8,light.yP()/8)||
					contains((light.xP())/8,(light.yP()+light.hP()-1)/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP())/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP()+light.hP()-1)/8)
			)
			{
				copyLightList.add(light);
			}
		}

	}

	//===============================================================================================
	public void pasteObjects()
	{//===============================================================================================


		if(MapCanvas.selectedAllLayers!=true)return;

		if(isCopiedOrCut!=true)return;
		//get the offset from copyXY

		//check if it is the same map as copyMap

		//check if we've copied or cut the objects

		Map m = MC.getMap();
		MapState state = m.getSelectedState();

		m.setSelectedAreaIndex(-1);
		m.setSelectedDoorIndex(-1);
		m.setSelectedLightIndex(-1);
		m.setSelectedEntityIndex(-1);


		int offsetx = x1 - copyX;
		int offsety = y1 - copyY;


		for(int i=0;i<copyAreaList.size();i++)
		{

			Area area = null;

			if(cutObjects)area = copyAreaList.get(i);
			if(copiedObjects)area = copyAreaList.get(i).duplicate(m,state);

			area.setMap(m);
			area.setState(state);

			area.setName(m.createUniqueAreaName(area.name(), -1));
			area.setXPixels(area.xP()+offsetx*8);
			area.setYPixels(area.yP()+offsety*8);
			area.setArrivalXPixels(area.arrivalXPixels()+offsetx*8);
			area.setArrivalYPixels(area.arrivalYPixels()+offsety*8);
			m.addArea(area);
		}

		for(int i=0;i<copyEntityList.size();i++)
		{

			Entity entity = null;

			if(cutObjects)entity = copyEntityList.get(i);
			if(copiedObjects)entity = copyEntityList.get(i).duplicate(m,state);

			entity.setMap(m);
			entity.setState(state);

			entity.setName(m.createUniqueEntityName(entity.name(), -1));
			entity.setXPixels(entity.xP()+offsetx*8);
			entity.setYPixels(entity.yP()+offsety*8);

			m.addEntity(entity);
		}

		for(int i=0;i<copyDoorList.size();i++)
		{

			Door door = null;

			if(cutObjects)door = copyDoorList.get(i);
			if(copiedObjects)door = copyDoorList.get(i).duplicate(m);

			door.setMap(m);

			door.setName(m.createUniqueDoorName(door.name(), -1));
			door.setXPixels(door.xP()+offsetx*8);
			door.setYPixels(door.yP()+offsety*8);
			door.setArrivalXPixels(door.arrivalXPixels()+offsetx*8);
			door.setArrivalYPixels(door.arrivalYPixels()+offsety*8);
			m.addDoor(door);
		}

		for(int i=0;i<copyLightList.size();i++)
		{

			Light light = null;

			if(cutObjects)light = copyLightList.get(i);
			if(copiedObjects)light = copyLightList.get(i).duplicate(m,state);

			light.setMap(m);
			light.setState(state);

			light.setName(m.createUniqueLightName(light.name(), -1));
			light.setXPixels(light.xP()+offsetx*8);
			light.setYPixels(light.yP()+offsety*8);
			light.setToggleXPixels(light.toggleXPixels1X()+offsetx*8);
			light.setToggleYPixels(light.toggleYPixels1X()+offsety*8);
			m.addLight(light);
		}


		copyEntityList.clear();
		copyLightList.clear();
		copyDoorList.clear();
		copyAreaList.clear();




		//if it is the same map and we've copied them, just add the copy list to the current map with a unique name.
		//for each object in the copy list, just set the mapXY to the offset.


		//if it is the same map and we've cut them
		//for each object in the copy list, just set the mapXY to the offset. that's it.


		//if it is a different map and we've copied them, add the copy list to the current map with a unique name.
		//for each object in the copy list, just set the mapXY to the offset.


		//if it is a different map and we've cut them, delete them from the original map lists
		//this will leave any remaining objects on the map with connections to this object broken.
		//add them to the current map with unique name.
		//for each object in the copy list, just set the mapXY to the offset.


		//it is basically all the same behavior if we ignore the connections list.
		//i decided to not mess with those, if they get broken, the client should handle ignoring this, the tools should highlight them in red in the connectionlist and also output any broken ones.



	}
	//===============================================================================================
	public void copyObjectsIfEnabled()
	{//===============================================================================================
		//make temp linked list of doors, areas, lights, entities under the selection
		copyEntityList.clear();
		copyLightList.clear();
		copyDoorList.clear();
		copyAreaList.clear();


		Map m = MC.getMap();

		m.setSelectedAreaIndex(-1);
		m.setSelectedDoorIndex(-1);
		m.setSelectedLightIndex(-1);
		m.setSelectedEntityIndex(-1);

		copyX = x1;
		copyY = y1;
		//used for calculating the offset from the copy position to the paste position

		copiedObjects=true;
		cutObjects = false;

		copyMap = m;

		//move lights, doors, sprites, actions


		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_AREA_LAYER].isSelected())
		for(int i=0;i<m.getNumAreas();i++)
		{
			Area area = m.getArea(i);
			if(
					contains(area.xP()/8,area.yP()/8)||
					contains((area.xP())/8,(area.yP()+area.hP()-1)/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP())/8)||
					contains((area.xP()+area.wP()-1)/8,(area.yP()+area.hP()-1)/8)
			)
			{
				copyAreaList.add(area);
			}

		}

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_DOOR_LAYER].isSelected())
		for(int i=0;i<m.getNumDoors();i++)
		{

			Door door = m.getDoor(i);

			if(
					contains(door.xP()/8,door.yP()/8)||
					contains((door.xP())/8,(door.yP()+door.hP()-1)/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP())/8)||
					contains((door.xP()+door.wP()-1)/8,(door.yP()+door.hP()-1)/8)
			)
			{
				copyDoorList.add(door);
			}

		}

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_ENTITY_LAYER].isSelected())
		for(int i=0;i<m.getNumEntities();i++)
		{
			Entity entity = m.getEntity(i);

			if(
					contains(entity.xP()/8,entity.yP()/8)||
					contains((entity.xP())/8,(entity.yP()+(int)((entity.hP()-1)))/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(entity.yP())/8)||
					contains((entity.xP()+(int)((entity.wP()-1)))/8,(int)(entity.yP()+((entity.hP()-1)))/8)
			)
			{
				copyEntityList.add(entity);
			}
		}

		if(EditorMain.controlPanel.showLayerCheckbox[MapData.MAP_LIGHT_LAYER].isSelected())
		for(int i=0;i<m.getNumLights();i++)
		{
			Light light = m.getLight(i);

			if(
					contains(light.xP()/8,light.yP()/8)||
					contains((light.xP())/8,(light.yP()+light.hP()-1)/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP())/8)||
					contains((light.xP()+light.wP()-1)/8,(light.yP()+light.hP()-1)/8)
			)
			{
				copyLightList.add(light);
			}
		}

	}

	//===============================================================================================
	public void copyEnabledLayers()
	{//===============================================================================================

		if(isShowing)
		{

				copyWidth = x2 - x1;
				copyHeight = y2 - y1;
				copy = new int[copyWidth][copyHeight][MapData.layers];

				isCopiedOrCut = false;

				int notblank = 0;

				//--------------check for not blank

				for(int l = 0; l < MapData.layers; l++)
				{
					if(MapData.isTileLayer(l) && EditorMain.controlPanel.showLayerCheckbox[l].isSelected())
					for(int y = 0; y < copyHeight; y++)
					{
						for(int x = 0; x < copyWidth; x++)
						{
							if(Project.getSelectedMap().getTileIndex(l, x1 + x, y1 + y) != 0)
							{
								y = copyHeight;
								x = copyWidth;
								l = MapData.layers;
								notblank = 1;
							}
						}
					}
				}


				if(notblank == 1)
				{
					for(int l = 0; l < MapData.layers; l++)//HYPER LAYER
					{
						if(MapData.isTileLayer(l) && EditorMain.controlPanel.showLayerCheckbox[l].isSelected())
						for(int y = 0; y < copyHeight; y++)
						{
							for(int x = 0; x < copyWidth; x++)
							{
								copy[x][y][l] = Project.getSelectedMap().getTileIndex(l, x1 + x, y1 + y); // Copy tiles within Selected Area
							}
						}
					}
					isCopiedOrCut = true;
					
					copyObjectsIfEnabled();
					
					EditorMain.infoLabel.setTextSuccess("Copied ENABLED LAYERS: " + (x2 - x1) + "x" + (y2 - y1));
				}
				else
				{
					EditorMain.infoLabel.setTextError("Did not copy: Selection was blank on Enabled Layers");
				}

		}


	}

	//===============================================================================================
	public void copyTiles()
	{//===============================================================================================

		if(isShowing)
		{

			if(MapCanvas.selectedAllLayers) //bob 20060523
			{
				copyWidth = x2 - x1;
				copyHeight = y2 - y1;
				copy = new int[copyWidth][copyHeight][MapData.layers];

				isCopiedOrCut = false;

				int notblank = 0;

				//--------------check for not blank

				for(int l = 0; l < MapData.layers; l++)
				{
					if(MapData.isTileLayer(l))
					for(int y = 0; y < copyHeight; y++)
					{
						for(int x = 0; x < copyWidth; x++)
						{
							if(Project.getSelectedMap().getTileIndex(l, x1 + x, y1 + y) != 0)
							{
								y = copyHeight;
								x = copyWidth;
								l = MapData.layers;
								notblank = 1;
							}
						}
					}
				}


				if(notblank == 1)
				{
					for(int l = 0; l < MapData.layers; l++)//HYPER LAYER
					{
						if(MapData.isTileLayer(l))
						for(int y = 0; y < copyHeight; y++)
						{
							for(int x = 0; x < copyWidth; x++)
							{
								copy[x][y][l] = Project.getSelectedMap().getTileIndex(l, x1 + x, y1 + y); // Copy tiles within Selected Area
							}
						}
					}
					isCopiedOrCut = true;
					EditorMain.infoLabel.setTextSuccess("Copied ALL LAYERS: " + (x2 - x1) + "x" + (y2 - y1));
				}
				else
				{
					EditorMain.infoLabel.setTextError("Did not copy: Selection was blank on All Layers");
				}




			}
			else
			{
				copyWidth = x2 - x1;
				copyHeight = y2 - y1;
				copy = new int[copyWidth][copyHeight][1];//HYPER LAYER

				isCopiedOrCut = false;

				if(MapData.isTileLayer(MapCanvas.selectedLayer))
				{

					int notblank = 0;

					for(int y = 0; y < copyHeight; y++)
					{
						for(int x = 0; x < copyWidth; x++)
						{
							if(Project.getSelectedMap().getTileIndex(MapCanvas.selectedLayer, x1 + x, y1 + y) != 0)
							{
								y = copyHeight;
								x = copyWidth;
								notblank = 1;
							}
						}
					}

					if(notblank == 1)
					{
						for(int y = 0; y < copyHeight; y++)
						{
							for(int x = 0; x < copyWidth; x++)
							{
								copy[x][y][0] = Project.getSelectedMap().getTileIndex(MapCanvas.selectedLayer, x1 + x, y1 + y); // Copy tiles within Selected Area
							}
						}
						EditorMain.infoLabel.setTextSuccess("Copied Area: " + (x2 - x1) + "x" + (y2 - y1));
						isCopiedOrCut = true;
					}
					else
					{
						EditorMain.infoLabel.setTextError("Did not copy: Selection was blank.");
					}

				}




			}
		}


	}


	//===============================================================================================
	public void copy()
	{//===============================================================================================
		copyTiles();
		copyObjects();

	}


	//===============================================================================================
	public void copyFromTo(int toX, int toY, int fromX, int fromY)
	{//===============================================================================================

		//copy, move selection box, paste

		copyTiles();
		copyObjects();
		moveSelectionBoxPositionByAmt(toX - fromX, toY - fromY);
		if(isCopiedOrCut)
		{
			paste();
			pasteObjects();
		}


	}



	//===============================================================================================
	public void swapTile(int l, int toX, int toY, int fromX, int fromY, CompoundEdit edit)
	{//===============================================================================================

		if(MapData.isTileLayer(l)==false)return;

		int tile1 = MC.getMap().getTileIndex(l, toX, toY);
		int tile2 = MC.getMap().getTileIndex(l, fromX, fromY);
		
		if(tile1 != tile2) {
			if(edit != null) {
				edit.addEdit(new TileChangeEdit(MC, l, toX, toY, tile1, tile2));
				edit.addEdit(new TileChangeEdit(MC, l, fromX, fromY, tile2, tile1));
			}
			
			MC.getMap().setTileIndex(l, toX, toY, tile2);
			MC.paintTileXY(l,toX,toY);
			MC.getMap().setTileIndex(l, fromX, fromY, tile1);
			MC.paintTileXY(l, fromX, fromY);
		}
	}
	
	//===============================================================================================
	public void swapTile(int l, int toX, int toY, int fromX, int fromY)
	{//===============================================================================================
		swapTile(l, toX, toY, fromX, fromY, null);
	}
	//===============================================================================================
	public void swapFromTo(int toX, int toY, int fromX, int fromY)
	{//===============================================================================================

		CompoundEdit edit = new CompoundEdit();

		if(MapCanvas.selectedAllLayers && isShowing && contains(fromX, fromY))
		{

			int offsetx = toX - fromX;
			int offsety = toY - fromY;
			for(int l = 0; l < MapData.layers; l++)//HYPER LAYER
			{

				if(MapData.isTileLayer(l))
				{

					if(offsety < 0)
					{
						for(int yy = y1; yy < y2; yy++)
						{
							if(offsetx < 0)
							{
								for(int xx = x1; xx < x2; xx++)
								{
									swapTile(l, xx + offsetx, yy + offsety, xx, yy, edit);
								}
							}
							else
							{
								for(int xx = x2 - 1; xx >= x1; xx--)
								{
									swapTile(l, xx + offsetx, yy + offsety, xx, yy, edit);
								}
							}
						}
					}
					else
					{
						for(int yy = y2 - 1; yy >= y1; yy--)
						{
							if(offsetx < 0)
							{
								for(int xx = x1; xx < x2; xx++)
								{
									swapTile(l, xx + offsetx, yy + offsety, xx, yy, edit);
								}
							}
							else
							{
								for(int xx = x2 - 1; xx >= x1; xx--)
								{
									swapTile(l, xx + offsetx, yy + offsety, xx, yy, edit);
								}
							}
						}
					}

				}

			}




			//move lights, doors, sprites, actions

			Map m = MC.getMap();

			for(int i=0;i<m.getNumAreas();i++)
			{

				Area area = m.getArea(i);

				if(
						contains(area.xP()/8,area.yP()/8)||
						contains((area.xP())/8,(area.yP()+area.hP()-1)/8)||
						contains((area.xP()+area.wP()-1)/8,(area.yP())/8)||
						contains((area.xP()+area.wP()-1)/8,(area.yP()+area.hP()-1)/8)
				)
				{
					int oldX = area.xP();
					int oldY = area.yP();
					int newX = area.xP()+offsetx*8;
					int newY = area.yP()+offsety*8;
					
					edit.addEdit(new MapObjectMoveEdit(area, oldX, oldY, newX, newY));

					//System.out.println("x: "+offsetx);
					//System.out.println("y: "+offsety);
					area.setXPixels(newX);
					area.setYPixels(newY);
					area.setArrivalXPixels(area.arrivalXPixels()+offsetx*8);
					area.setArrivalYPixels(area.arrivalYPixels()+offsety*8);
				}

			}

			for(int i=0;i<m.getNumDoors();i++)
			{

				Door door = m.getDoor(i);

				if(
						contains(door.xP()/8,door.yP()/8)||
						contains((door.xP())/8,(door.yP()+door.hP()-1)/8)||
						contains((door.xP()+door.wP()-1)/8,(door.yP())/8)||
						contains((door.xP()+door.wP()-1)/8,(door.yP()+door.hP()-1)/8)
				)
				{
					int oldX = door.xP();
					int oldY = door.yP();
					int newX = door.xP()+offsetx*8;
					int newY = door.yP()+offsety*8;
					
					edit.addEdit(new MapObjectMoveEdit(door, oldX, oldY, newX, newY));
					
					door.setXPixels(newX);
					door.setYPixels(newY);
					door.setArrivalXPixels(door.arrivalXPixels()+offsetx*8);
					door.setArrivalYPixels(door.arrivalYPixels()+offsety*8);
				}

			}

			for(int i=0;i<m.getNumEntities();i++)
			{
				Entity entity = m.getEntity(i);

				if(
						contains(entity.xP()/8,entity.yP()/8)||
						contains((entity.xP())/8,(entity.yP()+(int)((entity.hP()-1)))/8)||
						contains((entity.xP()+(int)((entity.wP()-1)))/8,(entity.yP())/8)||
						contains((entity.xP()+(int)((entity.wP()-1)))/8,(int)(entity.yP()+((entity.hP()-1)))/8)
				)
				{
					int oldX = entity.xP();
					int oldY = entity.yP();
					int newX = entity.xP()+offsetx*8;
					int newY = entity.yP()+offsety*8;
					
					edit.addEdit(new MapObjectMoveEdit(entity, oldX, oldY, newX, newY));
					
					entity.setXPixels(newX);
					entity.setYPixels(newY);
				}
			}

			for(int i=0;i<m.getNumLights();i++)
			{
				Light light = m.getLight(i);

				if(
						contains(light.xP()/8,light.yP()/8)||
						contains((light.xP())/8,(light.yP()+light.hP()-1)/8)||
						contains((light.xP()+light.wP()-1)/8,(light.yP())/8)||
						contains((light.xP()+light.wP()-1)/8,(light.yP()+light.hP()-1)/8)
				)
				{
					int oldX = light.xP();
					int oldY = light.yP();
					int newX = light.xP()+offsetx*8;
					int newY = light.yP()+offsety*8;
					
					edit.addEdit(new MapObjectMoveEdit(light, oldX, oldY, newX, newY));
					
					light.setXPixels(newX);
					light.setYPixels(newY);
					light.setToggleXPixels(light.toggleXPixels1X()+offsetx*8);
					light.setToggleYPixels(light.toggleYPixels1X()+offsety*8);
				}
			}


			moveSelectionBoxPositionByAmt(offsetx, offsety);
			MC.repaint();
			EditorMain.infoLabel.setTextError("Swapped area on ALL LAYERS");


		}
		else
		if(isShowing && contains(fromX, fromY))
		{

			int offsetx = toX - fromX;
			int offsety = toY - fromY;

			if(MapData.isTileLayer(MapCanvas.selectedLayer))
			{

				if(offsety < 0)
				{
					for(int yy = y1; yy < y2; yy++)
					{
						if(offsetx < 0)
						{
							for(int xx = x1; xx < x2; xx++)
							{
								swapTile(MapCanvas.selectedLayer, xx + offsetx, yy + offsety, xx, yy, edit);
							}
						}
						else
						{
							for(int xx = x2 - 1; xx >= x1; xx--)
							{
								swapTile(MapCanvas.selectedLayer, xx + offsetx, yy + offsety, xx, yy, edit);
							}
						}
					}
				}
				else
				{
					for(int yy = y2 - 1; yy >= y1; yy--)
					{
						if(offsetx < 0)
						{
							for(int xx = x1; xx < x2; xx++)
							{
								swapTile(MapCanvas.selectedLayer, xx + offsetx, yy + offsety, xx, yy, edit);
							}
						}
						else
						{
							for(int xx = x2 - 1; xx >= x1; xx--)
							{
								swapTile(MapCanvas.selectedLayer, xx + offsetx, yy + offsety, xx, yy, edit);
							}
						}
					}
				}
			}
			moveSelectionBoxPositionByAmt(offsetx, offsety);
			MC.repaint();
			EditorMain.infoLabel.setTextSuccess("Swapped Area");
		}
		
		edit.end();
		if(edit.isSignificant()) MC.undoManager.addEdit(edit);
	}





	//===============================================================================================
	public void cut()
	{//===============================================================================================

		if(isShowing)
		{
			copyTiles();

			if(isCopiedOrCut)
			{
				delete();
				cutObjects();

				if(MapCanvas.selectedAllLayers)
				{
					EditorMain.infoLabel.setTextError("Cut ALL LAYERS: " + (x2 - x1) + "x" + (y2 - y1));
				}
				else
				{
					EditorMain.infoLabel.setTextSuccess("Cut Area: " + (x2 - x1) + "x" + (y2 - y1));
				}

			}





		}

	}

	//===============================================================================================
	public void delete()
	{//===============================================================================================


		if(isShowing)
		{
			if(MapCanvas.selectedAllLayers)
			{
				for(int yy = y1; yy < y2; yy++)
				{
					for(int xx = x1; xx < x2; xx++)
					{
						int l = 0;
						for(l = 0; l < MapData.layers; l++)
						{
							if(MapData.isTileLayer(l))
							{
								MC.getMap().setTileIndex(l, xx, yy, 0);
								MC.paintTileXY(l, xx, yy);
							}
						}
					}
				}

				MC.repaint();
				EditorMain.infoLabel.setTextError("Deleted ALL LAYERS Area: " + (x2 - x1) + "x" + (y2 - y1));
			}
			else
			{
				if(MapData.isTileLayer(MapCanvas.selectedLayer))
				{
					for(int yy = y1; yy < y2; yy++)
					{
						for(int xx = x1; xx < x2; xx++)
						{
							MC.getMap().setTileIndex(MapCanvas.selectedLayer, xx, yy, 0);
							MC.paintTileXY(MapCanvas.selectedLayer, xx, yy);
						}
					}
				}

				MC.repaint();
				EditorMain.infoLabel.setTextSuccess("Deleted Area: " + (x2 - x1) + "x" + (y2 - y1));
			}

		}



	}


	//===============================================================================================
	public boolean paste()
	{//===============================================================================================


		if(
				isShowing &&
				isCopiedOrCut &&
				copyWidth <= getWidth() &&
				copyHeight <= getHeight()

		)
		{
			if(MapCanvas.selectedAllLayers)
			{


				for(int l = 0; l < MapData.layers; l++)//HYPER LAYER
				{
					if(MapData.isTileLayer(l))
					for(int y = 0; y < copyHeight; y++)
					{
						for(int x = 0; x < copyWidth; x++)
						{

							Project.getSelectedMap().setTileIndex(l, x1 + x, y1 + y, copy[x][y][l]); // Paste tiles within Selected Area

							MC.paintTileXY(l, x1 + x, y1 + y);
						}
					}
				}


				pasteObjects();

				MC.repaint();
				EditorMain.infoLabel.setTextError("Pasted Tiles for ALL LAYERS");
				return true;
			}
			else
			if(MapData.isTileLayer(MapCanvas.selectedLayer))
			{

				for(int y = 0; y < copyHeight; y++)
				{
					for(int x = 0; x < copyWidth; x++)
					{

						Project.getSelectedMap().setTileIndex(MapCanvas.selectedLayer, x1 + x, y1 + y, copy[x][y][0]); // Paste tiles within Selected Area
						MC.paintTileXY(MapCanvas.selectedLayer, x1 + x, y1 + y);

					}
				}
				MC.repaint();
				EditorMain.infoLabel.setTextSuccess("Pasted Tiles");
				return true;
			}
			else
			{
				EditorMain.infoLabel.setTextError("Cannot paste into a non-tile layer");
				return false;
			}
		}
		else
		{
			if(!isShowing)EditorMain.infoLabel.setTextError("Cannot paste, there is no selection to paste into");
			if(!isCopiedOrCut)EditorMain.infoLabel.setTextError("Cannot paste, there is nothing copied");
			if(!(copyWidth <= getWidth())||!(copyHeight <= getHeight()))EditorMain.infoLabel.setTextError("Cannot paste, the selection is too small to paste into");
			return false;
		}

	}



	//===============================================================================================
	public boolean pasteReverse()
	{//===============================================================================================
		if(
				isShowing &&
				isCopiedOrCut &&
				copyWidth <= getWidth() &&
				copyHeight <= getHeight() &&
				MapData.isTileLayer(MapCanvas.selectedLayer)
		)
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{

					Project.getSelectedMap().setTileIndex(MapCanvas.selectedLayer, x2 - x - 1, y1 + y, copy[x][y][0]);
					MC.paintTileXY(MapCanvas.selectedLayer, x2 - x - 1, y1 + y);

				}
			}
			MC.repaint();
			return true;
		}
		else
		{
			return false;
		}
	}

	//===============================================================================================
	public boolean pasteFlipped()
	{//===============================================================================================
		if(
				isShowing &&
				isCopiedOrCut &&
				copyWidth <= getWidth() &&
				copyHeight <= getHeight() &&
				MapData.isTileLayer(MapCanvas.selectedLayer)

		)
		{
			for(int y = 0; y < copyHeight; y++)
			{
				for(int x = 0; x < copyWidth; x++)
				{
					Project.getSelectedMap().setTileIndex(MapCanvas.selectedLayer, x1 + x, y2 - y - 1, copy[x][y][0]);
					MC.paintTileXY(MapCanvas.selectedLayer, x1 + x, y2 - y - 1);
				}
			}
			MC.repaint();
			return true;
		}
		else
		{
			return false;
		}
	}


}
