//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------


#pragma once
#include "bobtypes.h"
class Logger;




class MapStateData : public AssetData
{

private:
	typedef AssetData super;




private:
	
	ArrayList<std::shared_ptr<LightData>> lightDataList;

	
	ArrayList<std::shared_ptr<EntityData>> entityDataList;

	//public ArrayList<EntityData> characterDataList = new ArrayList<EntityData>();

	
	ArrayList<std::shared_ptr<AreaData>> areaDataList;


	
	int mapID = -1;


public:
	MapStateData();


	MapStateData(int id, const string& name);


	//static MapStateData* fromBase64ZippedJSON(const string& b64);
	//static MapStateData* fromJSON(const string& json);

	string& initFromString(string& t);

	string getTYPEIDString();

	ArrayList<std::shared_ptr<LightData>>* getLightDataList();
	ArrayList<std::shared_ptr<EntityData>>* getEntityDataList();
	ArrayList<std::shared_ptr<AreaData>>* getAreaDataList();


	int getMapID();

	void setMapID(int s);
};

