//------------------------------------------------------------------------------
//Copyright Robert Pelloni.
//All Rights Reserved.
//------------------------------------------------------------------------------

#pragma once
#include "bobtypes.h"
#include "Entity.h"
class Logger;

class PathFinder;
class Engine;
class EntityData;
class BobTexture;
class Caption;
class Sprite;
class Area;

class Character : public Entity
{
public:
	static Logger log;

	int standing_cycles = 0;

	int pixelsToWalk = 0;
	int xPixelCounter = 0;
	int yPixelCounter = 0;

	int ticksToStand = 0;

	int animationDirection = 0;

	std::shared_ptr<PathFinder> pathfinder = nullptr;

	int pathPosition = 0;

	int pathFindWaitTicks = 0;

	float lastMapX = 0;
	float lastMapY = 0;
	int ticksSinceMoved = 0;

	bool moved = false;
	bool standing = false;
	bool running = false;

	std::shared_ptr<BobTexture> uniqueTexture = nullptr;

	bool showName = false;
	std::shared_ptr<Caption> nameCaption = nullptr;

	bool showAccountType = false;
	std::shared_ptr<Caption> accountTypeCaption = nullptr;

	BobColor nameColor = *BobColor::white;
	BobColor accountTypeNameColor = *BobColor::white;
	string accountTypeName = "";

	bool isMale = false;
	bool isFemale = false;

	int standingTicksBetweenFrames = 0;
	int rotationAnimationSpeedTicks = 160;

	Character();

	Character(Engine* g, std::shared_ptr<EntityData> data, std::shared_ptr<Map> m);

	void initCharacter();

	Character(Engine* g, string name, std::shared_ptr<Sprite> sprite, std::shared_ptr<Area> a, std::shared_ptr<Map> m);

	virtual void initCurrentAnimationFromSprite() override;

	virtual void render(float alpha) override;

	virtual void update() override;

	void setAnimationByDirection(int dir);

	bool canDoCharacterMovementOrStandingAnimation();

	void doCharacterAnimation();

	void checkIfMoved();

	void dontLookAtEntity(std::shared_ptr<Entity> e);

	void lookAtEntity(std::shared_ptr<Entity> e);

	void lookAtEntityButNotOppositeWalkingDirection(std::shared_ptr<Entity> stared_at_entity);

	void setAppearanceFromCharacterAppearanceString(string s);

	void generateUniqueTexture(int genderIndex, int archetypeIndex, int shoeColorIndex, int shirtColorIndex, int pantsColorIndex, int skinColorIndex, int eyeColorIndex, int hairColorIndex);

	void setShowName(bool b);

	void setShowAccountType(bool b);

	void setCharacterNameAndCaption(BobColor nameColor, const string& name, BobColor accountTypeNameColor, const string& accountTypeName);

	ArrayList<std::shared_ptr<Entity>>* getOnScreenNonCharacterEntitiesWithinRangeAmount(int amt);

	bool checkTouchingAnyEntityInEntityList(ArrayList<std::shared_ptr<Entity>>* list, float x, float y);

	bool checkHitLayerAndTouchingAnyEntityInEntityList(ArrayList<std::shared_ptr<Entity>>* list, float x, float y);

	bool checkTouchingAnyOnScreenNonCharacterNonWalkableEntities(float x, float y);

	void setShadowClip();

	int pathTried = 0;

	float finalPathX = 0;
	float finalPathY = 0;


	int walkToXYWithPathFinding(float x, float y);

	void checkHitBoxAndWalkDirection(int dir);

	void walkDirectionNoCheckHit(int direction);

	void walkRandomlyAroundRoomAndStop();

	void walkRandomlyAroundRoom();

	int walkRandomlyWithinXYXY(float x1, float y1, float x2, float y2);

	void twitchAroundRoom();

	std::shared_ptr<Character> findNearestCharacter();

	int walkToXYLRToUD(float x, float y);

	int walkToXYUDToLR(float toX, float toY);

	bool walkToXYNoCheckHit(float toX, float toY);

	bool walkToXYNoCheckHitOLD(float x, float y);

	bool walkToXYUntilHitWall(float x, float y);

	int walkToXYWithBasicHitCheck(float x, float y);

	int walkToXYNoHitAvoidOthersPushMain(float x, float y);

	int walkToXYStopForOtherEntitiesWithinAmt(float x, float y, int amt);

	void walkDirectionAvoidOtherEntities(int direction);


	bool walkToXYIntelligentHitPushOthers(float x, float y);

	bool walkToXYIntelligentHitAvoidOthers(float x, float y);

	int walk_to_xy_intelligenthit_stopforothers_pushmain(float x, float y);

	void walkStraightFromPointToPoint(float x1, float y1, float x2, float y2);

	void walkStraightFromPointToPointAndStop(float x1, float y1, float x2, float y2);

	void walkAwayFromPoint(float x, float y);

	int walkDistance(int direction);

	int avoidEntity(std::shared_ptr<Entity> e, int amt);

	int avoidNearestEntity(int avoid_amt);

	int avoidNearestCharacter(int avoid_amt);

	void pushableCrowdBehavior();

	int walk_to_xy_intelligenthit_avoidothers_pushmain(float x, float y);

	virtual void renderDebugBoxes() override;
};
