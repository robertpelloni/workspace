//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;
#include <deque>



class PotentialTile;
class Comparable;
class TilePath;


class PathTile
{ //=========================================================================================================================
private:
	//TilePath* outerInstance = nullptr;


public:
	int tileX = 0;
	int tileY = 0;


	PathTile(int tileX, int tileY);//TilePath* outerInstance, 


	int getX();


	int getY();


	int hashCode();


	//bool equals(void* other);
};

//=========================================================================================================================

class TilePath
{ //=========================================================================================================================
private:
	//PathFinder* outerInstance = nullptr;


public:
	deque<shared_ptr<PathTile>> pathTiles;


	TilePath();// PathFinder* outerInstance);


	int getLength();


	shared_ptr<PathTile> getTileForPathIndex(int index);


	int getTileXForPathIndex(int index);


	int getTileYForPathIndex(int index);


	void addPathTileToEnd(int x, int y);


	void addPathTileToBeginning(int x, int y);


	bool doesPathContain(int tileX, int tileY);

	//=========================================================================================================================
public:
};

class SortedList
{ //=========================================================================================================================
private:
	//PathFinder* outerInstance = nullptr;

public:
	SortedList();// PathFinder* outerInstance);

	/// <summary>
	/// The list of elements </summary>
private:
	ArrayList<shared_ptr<PotentialTile>> list;


	/// <summary>
	/// Retrieve the first element from the list
	/// </summary>
	/// <returns> The first element from the list </returns>
public:
	shared_ptr<PotentialTile> first();


	/// <summary>
	/// Empty the list
	/// </summary>
	void clear();


	void addAndSort(shared_ptr<PotentialTile> o);


	void remove(shared_ptr<PotentialTile> o);


	int size();


	bool contains(shared_ptr<PotentialTile> o);
};

class PotentialTile
{ //=========================================================================================================================
public:
	//PathFinder* outerInstance = nullptr;


	/// <summary>
	/// The x coordinate of the node </summary>
	int x = 0;
	/// <summary>
	/// The y coordinate of the node </summary>
	int y = 0;
	/// <summary>
	/// The path cost for this node </summary>
	float cumulativePathCost = 0;
	/// <summary>
	/// The parent of this node, how we reached it in the search </summary>
	PotentialTile* parent;
	/// <summary>
	/// The heuristic cost of this node </summary>
	float heuristicCost = 0;
	/// <summary>
	/// The search depth of this node </summary>
	int depth = 0;


	//=========================================================================================================================
public:
	PotentialTile(int x, int y);


	//=========================================================================================================================
	int setParentTile(PotentialTile* parent);


	/// <seealso cref= Comparable#compareTo(Object) </seealso>
	//=========================================================================================================================
	int compareTo(PotentialTile* o);
};


class PathFinder
{ //=========================================================================================================================


	//=========================================================================================================================
private:


	/// <summary>
	/// A single node in the search graph
	/// </summary>
	//=========================================================================================================================


public:
	shared_ptr<TilePath> path = nullptr;

private:
	ArrayList<shared_ptr<PotentialTile>> blockedPotentialTilesList;
	SortedList openPotentialTilesList;

	//ArrayList<ArrayList<PotentialTile*>*>* potentialTiles = new ArrayList<ArrayList<PotentialTile*>*>();
	vector<shared_ptr<PotentialTile>> potentialTiles;
	vector<bool> checkedTileArray;


	int maxSearchDistance = 0;
	bool allowDiagMovement = false;

public:
	Entity* e = nullptr;


	int w = 0;
	int h = 0;


	//=========================================================================================================================
	PathFinder(Entity* e, float middleStartXPixelsHQ, float middleStartYPixelsHQ, float finishXPixelsHQ, float finishYPixelsHQ, int mapWidthTiles1X, int mapHeightTiles1X);


	//=========================================================================================================================
	shared_ptr<TilePath> findPath(int startTileX, int startTileY, int toTileX, int toTileY);


	//=========================================================================================================================
	bool isTileBlocked(int tileX, int tileY);


private:
	int minCost = 0;
	//=========================================================================================================================
public:
	int getHeuristicCost(int tileX, int tileY, int endTileX, int endTileY);

	//=========================================================================================================================
	int getTileTypeCost(int fromTileX, int fromTileY, int toTileX, int toTileY);


	//=========================================================================================================================
	void setTileChecked(int tileX, int tileY);


	//=========================================================================================================================
	bool wasTileChecked(int tileX, int tileY);


	//=========================================================================================================================
protected:
	bool isValidLocation(int currentTileX, int currentTileY, int checkTileX, int checkTileY);
};

