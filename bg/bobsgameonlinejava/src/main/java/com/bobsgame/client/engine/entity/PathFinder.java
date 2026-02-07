package com.bobsgame.client.engine.entity;



import java.util.ArrayList;
import java.util.Collections;

import com.bobsgame.client.engine.EnginePart;
import com.bobsgame.client.engine.map.MapManager;




//=========================================================================================================================
public class PathFinder
{// =========================================================================================================================



	// =========================================================================================================================
	public class TilePath
	{// =========================================================================================================================

		public ArrayList<PathTile> pathTiles=new ArrayList<PathTile>();


		public TilePath()
		{

		}


		public int getLength()
		{
			return pathTiles.size();
		}


		public PathTile getTileForPathIndex(int index)
		{
			return (PathTile)pathTiles.get(index);
		}


		public int getTileXForPathIndex(int index)
		{
			return getTileForPathIndex(index).tileX;
		}


		public int getTileYForPathIndex(int index)
		{
			return getTileForPathIndex(index).tileY;
		}


		public void addPathTileToEnd(int x,int y)
		{
			pathTiles.add(new PathTile(x,y));
		}


		public void addPathTileToBeginning(int x,int y)
		{
			pathTiles.add(0,new PathTile(x,y));
		}


		public boolean doesPathContain(int tileX,int tileY)
		{
			return pathTiles.contains(new PathTile(tileX,tileY));
		}

		// =========================================================================================================================
		public class PathTile
		{// =========================================================================================================================

			public int tileX;
			public int tileY;


			public PathTile(int tileX,int tileY)
			{
				this.tileX=tileX;
				this.tileY=tileY;
			}


			public int getX()
			{
				return tileX;
			}


			public int getY()
			{
				return tileY;
			}


			public int hashCode()
			{
				return tileX*tileY;
			}


			public boolean equals(Object other)
			{
				if(other instanceof PathTile)
				{
					PathTile o=(PathTile)other;
					return (o.tileX==tileX)&&(o.tileY==tileY);
				}

				return false;
			}
		}
	}



	// =========================================================================================================================
	private class SortedList
	{// =========================================================================================================================
		/** The list of elements */
		private ArrayList<PotentialTile> list=new ArrayList<PotentialTile>();


		/**
		 * Retrieve the first element from the list
		 *
		 * @return The first element from the list
		 */
		public PotentialTile first()
		{
			return list.get(0);
		}


		/**
		 * Empty the list
		 */
		public void clear()
		{
			list.clear();
		}


		public void addAndSort(PotentialTile o)
		{
			list.add(o);
			Collections.sort(list);
		}


		public void remove(PotentialTile o)
		{
			list.remove(o);
		}


		public int size()
		{
			return list.size();
		}


		public boolean contains(PotentialTile o)
		{
			return list.contains(o);
		}
	}

	/**
	 * A single node in the search graph
	 */
	// =========================================================================================================================
	private class PotentialTile implements Comparable<PotentialTile>
	{// =========================================================================================================================

		/** The x coordinate of the node */
		private int x;
		/** The y coordinate of the node */
		private int y;
		/** The path cost for this node */
		private float cumulativePathCost;
		/** The parent of this node, how we reached it in the search */
		private PotentialTile parent;
		/** The heuristic cost of this node */
		private float heuristicCost;
		/** The search depth of this node */
		private int depth;


		// =========================================================================================================================
		public PotentialTile(int x,int y)
		{// =========================================================================================================================
			this.x=x;
			this.y=y;
		}


		// =========================================================================================================================
		public int setParentTile(PotentialTile parent)
		{// =========================================================================================================================
			depth=parent.depth+1;
			this.parent=parent;

			return depth;
		}


		/**
		 * @see Comparable#compareTo(Object)
		 */
		// =========================================================================================================================
		public int compareTo(PotentialTile o)
		{// =========================================================================================================================

			float f=heuristicCost+cumulativePathCost;
			float of=o.heuristicCost+o.cumulativePathCost;

			if(f<of)
			{
				return -1;
			}
			else if(f>of)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}


	}



	public TilePath path;

	private ArrayList<PotentialTile> blockedPotentialTilesList=new ArrayList<PotentialTile>();
	private SortedList openPotentialTilesList=new SortedList();

	private PotentialTile[][] potentialTiles;
	private boolean[][] checkedTileArray;


	private int maxSearchDistance;
	private boolean allowDiagMovement;

	Entity e;


	public int w;
	public int h;




	// =========================================================================================================================
	public PathFinder(Entity e,float middleStartXPixelsHQ,float middleStartYPixelsHQ,float finishXPixelsHQ,float finishYPixelsHQ,int mapWidthTiles1X,int mapHeightTiles1X)
	{// =========================================================================================================================


		this.e = e;

		int characterWidth=(int)(e.right()-e.left());
		int characterHeight=(int)(e.bottom()-e.top());


		w = mapWidthTiles1X;
		h = mapHeightTiles1X;


		int startTileX=(((int)Math.floor(middleStartXPixelsHQ))/8)/2;
		int startTileY=(((int)Math.floor(middleStartYPixelsHQ))/8)/2;
		if(startTileX<=0) startTileX=1;
		if(startTileX>=w-1) startTileX=w-2;
		if(startTileY<=0) startTileY=1;
		if(startTileY>=h-1) startTileY=h-2;

		int finishTileX=(((int)Math.floor(finishXPixelsHQ))/8)/2;
		int finishTileY=(((int)Math.floor(finishYPixelsHQ))/8)/2;
		if(finishTileX<=0) finishTileX=1;
		if(finishTileX>=w-1) finishTileX=w-2;
		if(finishTileY<=0) finishTileY=1;
		if(finishTileY>=h-1) finishTileY=h-2;

		int slop=0;


		int origStartTileX=startTileX;
		int origStartTileY=startTileY;

		while(e.checkPathBlockedXY(startTileX*2*8+8,startTileY*2*8+8)==true
		// ||
		// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)-characterWidth/4,(startTileY*2*8)-characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)+characterWidth/4,(startTileY*2*8)-characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)-characterWidth/4,(startTileY*2*8)+characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((startTileX*2*8)+characterWidth/4,(startTileY*2*8)+characterHeight/4)==true
		)
		{

			if(slop==0)
			{
				startTileX=origStartTileX;
				startTileY=origStartTileY+1;
				slop++;
			}
			else if(slop==1)
			{
				startTileX=origStartTileX-1;
				startTileY=origStartTileY;
				slop++;
			}
			else if(slop==2)
			{
				startTileX=origStartTileX;
				startTileY=origStartTileY-1;
				slop++;
			}
			else if(slop==3)
			{
				startTileX=origStartTileX+1;
				startTileY=origStartTileY;
				slop++;
			}
			else if(slop==4)
			{
				startTileX=origStartTileX+1;
				startTileY=origStartTileY+1;
				slop++;
			}
			else if(slop==5)
			{
				startTileX=origStartTileX+1;
				startTileY=origStartTileY-1;
				slop++;
			}
			else if(slop==6)
			{
				startTileX=origStartTileX-1;
				startTileY=origStartTileY+1;
				slop++;
			}
			else if(slop==7)
			{
				startTileX=origStartTileX-1;
				startTileY=origStartTileY-1;
				slop++;
			}
			else if(slop==8)
			{
				startTileX=origStartTileX;
				startTileY=origStartTileY;
				slop++;
			}
			else if(slop<16)
			{

				slop++;
				if(finishXPixelsHQ<middleStartXPixelsHQ) startTileX--;
				else if(finishXPixelsHQ>middleStartXPixelsHQ) startTileX++;

				if(finishYPixelsHQ<middleStartYPixelsHQ) startTileY--;
				else if(finishYPixelsHQ>middleStartYPixelsHQ) startTileY++;
			}
			else return;
		}


		slop=0;


		int origFinishTileX=finishTileX;
		int origFinishTileY=finishTileY;

		while(e.checkPathBlockedXY(finishTileX*2*8+8,finishTileY*2*8+8)==true
		// ||
		// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)-characterWidth/4,(finishTileY*2*8)-characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)+characterWidth/4,(finishTileY*2*8)-characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)-characterWidth/4,(finishTileY*2*8)+characterHeight/4)==true||
		// map().checkHitLayerAndHitSpritesXY((finishTileX*2*8)+characterWidth/4,(finishTileY*2*8)+characterHeight/4)==true

		)
		{

			if(slop==0)
			{
				finishTileX=origFinishTileX;
				finishTileY=origFinishTileY+1;
				slop++;
			}
			else if(slop==1)
			{
				finishTileX=origFinishTileX-1;
				finishTileY=origFinishTileY;
				slop++;
			}
			else if(slop==2)
			{
				finishTileX=origFinishTileX;
				finishTileY=origFinishTileY-1;
				slop++;
			}
			else if(slop==3)
			{
				finishTileX=origFinishTileX+1;
				finishTileY=origFinishTileY;
				slop++;
			}
			else if(slop==4)
			{
				finishTileX=origFinishTileX+1;
				finishTileY=origFinishTileY+1;
				slop++;
			}
			else if(slop==5)
			{
				finishTileX=origFinishTileX+1;
				finishTileY=origFinishTileY-1;
				slop++;
			}
			else if(slop==6)
			{
				finishTileX=origFinishTileX-1;
				finishTileY=origFinishTileY+1;
				slop++;
			}
			else if(slop==7)
			{
				finishTileX=origFinishTileX-1;
				finishTileY=origFinishTileY-1;
				slop++;
			}
			else if(slop==8)
			{
				finishTileX=origFinishTileX;
				finishTileY=origFinishTileY;
				slop++;
			}
			else if(slop<16)
			{

				slop++;
				if(finishXPixelsHQ>middleStartXPixelsHQ) finishTileX--;
				else if(finishXPixelsHQ<middleStartXPixelsHQ) finishTileX++;

				if(finishYPixelsHQ>middleStartYPixelsHQ) finishTileY--;
				else if(finishYPixelsHQ<middleStartYPixelsHQ) finishTileY++;
			}
			else return;
		}

		// System.out.println("Width: "+mapWidth);
		// System.out.println("Height: "+mapHeight);
		// System.out.println("Start: "+startTileX+","+startTileY);
		// System.out.println("End: "+finishTileX+","+finishTileY);



		checkedTileArray=new boolean[w][h];



		this.maxSearchDistance=w+h;
		this.allowDiagMovement=false;

		potentialTiles=new PotentialTile[w][h];


		for(int x=0;x<w;x++)
		{
			for(int y=0;y<h;y++)
			{
				potentialTiles[x][y]=new PotentialTile(x,y);
			}
		}


		path=findPath(startTileX,startTileY,finishTileX,finishTileY);


	}



	// =========================================================================================================================
	public TilePath findPath(int startTileX,int startTileY,int toTileX,int toTileY)
	{// =========================================================================================================================


		// easy first check, if the destination is blocked, we can't get there
		if(isTileBlocked(toTileX,toTileY))
		{
			return null;
		}



		// initial state for A*. The closed group is empty. Only the starting
		// tile is in the open list and it's cost is zero, i.e. we're already there
		potentialTiles[startTileX][startTileY].cumulativePathCost=0;
		potentialTiles[startTileX][startTileY].depth=0;
		blockedPotentialTilesList.clear();
		openPotentialTilesList.clear();
		openPotentialTilesList.addAndSort(potentialTiles[startTileX][startTileY]);

		potentialTiles[toTileX][toTileY].parent=null;

		// while we haven't found the goal and haven't exceeded our max search depth
		int maxDepth=0;


		while((maxDepth<maxSearchDistance)&&(openPotentialTilesList.size()!=0))
		{
			// pull out the first node in our open list, this is determined to
			// be the most likely to be the next step based on our heuristic
			PotentialTile current=openPotentialTilesList.first();
			if(current==potentialTiles[toTileX][toTileY])
			{
				break;
			}

			openPotentialTilesList.remove(current);
			blockedPotentialTilesList.add(current);

			// search through all the neighbours of the current node evaluating
			// them as next steps
			for(int x=-1;x<2;x++)
			{
				for(int y=-1;y<2;y++)
				{
					// not a neighbour, its the current tile
					if((x==0)&&(y==0))
					{
						continue;
					}

					// if we're not allowing diaganol movement then only
					// one of x or y can be set
					if(!allowDiagMovement)
					{
						if((x!=0)&&(y!=0))
						{
							continue;
						}
					}

					// determine the location of the neighbour and evaluate it
					int xp=x+current.x;
					int yp=y+current.y;

					if(isValidLocation(startTileX,startTileY,xp,yp))
					{
						// the cost to get to this node is cost the current plus the movement
						// cost to reach this node. Note that the heursitic value is only used
						// in the sorted open list
						float nextStepCost=current.cumulativePathCost+getTileTypeCost(current.x,current.y,xp,yp);

						PotentialTile neighbour=potentialTiles[xp][yp];

						setTileChecked(xp,yp);

						// if the new cost we've determined for this node is lower than
						// it has been previously makes sure the node hasn't been discarded. We've
						// determined that there might have been a better path to get to
						// this node so it needs to be re-evaluated
						if(nextStepCost<neighbour.cumulativePathCost)
						{
							if(openPotentialTilesList.contains(neighbour))
							{
								openPotentialTilesList.remove(neighbour);
							}
							if(blockedPotentialTilesList.contains(neighbour))
							{
								blockedPotentialTilesList.remove(neighbour);
							}
						}

						// if the node hasn't already been processed and discarded then
						// reset it's cost to our current cost and add it as a next possible
						// step (i.e. to the open list)
						if(!openPotentialTilesList.contains(neighbour)&&!(blockedPotentialTilesList.contains(neighbour)))
						{
							neighbour.cumulativePathCost=nextStepCost;
							neighbour.heuristicCost=getHeuristicCost(xp,yp,toTileX,toTileY);
							maxDepth=Math.max(maxDepth,neighbour.setParentTile(current));
							openPotentialTilesList.addAndSort(neighbour);
						}
					}
				}
			}
		}

		// since we've got an empty open list or we've run out of search
		// there was no path. Just return null
		if(potentialTiles[toTileX][toTileY].parent==null)
		{
			return null;
		}



		// TODO: thread this.


		// At this point we've definitely found a path so we can uses the parent
		// references of the nodes to find out way from the target location back
		// to the start recording the nodes on the way.
		TilePath path=new TilePath();
		PotentialTile target=potentialTiles[toTileX][toTileY];
		while(target!=potentialTiles[startTileX][startTileY])
		{
			path.addPathTileToBeginning(target.x,target.y);
			target=target.parent;
		}
		path.addPathTileToBeginning(startTileX,startTileY);

		// thats it, we have our path
		return path;
	}




	// =========================================================================================================================
	public boolean isTileBlocked(int tileX,int tileY)
	{// =========================================================================================================================

		if(e.checkPathBlockedXY(tileX*8*2+8,tileY*8*2+8)==true // TODO: optimize this by checking hit layer directly.

		// ||
		// map().checkHitLayerAndHitSpritesXY((x-1)*8*2,y*8*2) == true ||
		// map().checkHitLayerAndHitSpritesXY((x+1)*8*2,y*8*2) == true
		// ||
		// map().checkHitLayerAndHitSpritesXY((x*8*2)-characterWidth/4,(y*8*2)-characterHeight/4) == true||
		// map().checkHitLayerAndHitSpritesXY((x*8*2)+characterWidth/4,(y*8*2)-characterHeight/4) == true||
		// map().checkHitLayerAndHitSpritesXY((x*8*2)-characterWidth/4,(y*8*2)+characterHeight/4) == true||
		// map().checkHitLayerAndHitSpritesXY((x*8*2)+characterWidth/4,(y*8*2)+characterHeight/4) == true

		) return true;

		return false;

	}


	private int minCost;
	// =========================================================================================================================
	public float getHeuristicCost(int tileX,int tileY,int endTileX,int endTileY)
	{// =========================================================================================================================
		return minCost*(Math.abs(tileX-endTileX)+Math.abs(tileY-endTileY));
	}

	// =========================================================================================================================
	public float getTileTypeCost(int fromTileX,int fromTileY,int toTileX,int toTileY)
	{// =========================================================================================================================
		// TODO: check if tile is marked as being grass, cement, near a guard rail, etc, and increase cost to avoid those areas unless necessary.

		return 1;
	}


	// =========================================================================================================================
	public void setTileChecked(int tileX,int tileY)
	{// =========================================================================================================================
		checkedTileArray[tileX][tileY]=true;
	}


	// =========================================================================================================================
	public boolean wasTileChecked(int tileX,int tileY)
	{// =========================================================================================================================
		return checkedTileArray[tileX][tileY];
	}



	// =========================================================================================================================
	protected boolean isValidLocation(int currentTileX,int currentTileY,int checkTileX,int checkTileY)
	{// =========================================================================================================================
		boolean invalid=(checkTileX<0)||(checkTileY<0)||(checkTileX>=w)||(checkTileY>=h);

		if((!invalid)&&((currentTileX!=checkTileX)||(currentTileY!=checkTileY)))
		{
			invalid=isTileBlocked(checkTileX,checkTileY);
		}

		return !invalid;
	}



}
