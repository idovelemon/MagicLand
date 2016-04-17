//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define all the entity's creator.In this class,
// all the creator is a static method and all the creator is in a map.
// If you want to add new entity, you must add a new creator in this map
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLENTITYCREATOR_H_
#define ML_ENTITYCOMPONENT_MLENTITYCREATOR_H_

#include <cocos2d.h>

#include "marco.h"
#include "entitycomponent/ml_entity.h"
#include "support/xjmath/XJMath.h"

namespace magicland {

struct MLETYCreatorEntry;
class MLRoom;

typedef MLEntity* (*PFUNCEntityCreator)(int xCoord, int yCoord, MLRoom* room);

struct magicland::MLETYCreatorEntry {
	MLEntitySubType type;
	PFUNCEntityCreator creator;
};

class MLEntityCreator {
protected:
	static MLETYCreatorEntry s_CreatorTable[];

private:
	MLEntityCreator();
	virtual ~MLEntityCreator();
	ML_DISALLOW_COPY_AND_ASSIGN(MLEntityCreator);

public:
	static MLEntity* CreateTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room);
	static MLEntity* CreateFireBall(float posx, float posy, magicland::MLDir dir, MLRoom* room);
	static MLEntity* CreateOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateJumpOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateMovePlatform(float posx, float posy, MLRoom* room);
	static MLEntity* CreateThrowOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateBoomBall(float posx, float posy, MLRoom* room);
	static MLEntity* CreateBrokenStone(float posx, float posy, float velx, float vely, MLRoom* room);
	static MLEntity* CreateGearCore(float posx, float posy, MLRoom* room);

	// Created from room map
public:
	static MLEntity* CreateEntity(MLEntitySubType type, int xCoord, int yCoord, MLRoom* room);
	
protected:
	static MLEntity* CreateWall(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateXJ(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateOrge(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateJumpOrge(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateMovePlatform(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateThrowOrge(int xCoord, int yCoord, MLRoom* room);
	static MLEntity* CreateGearCore(int xCoord, int yCoord, MLRoom* room);
};

}; // namespace magicland

#endif //ML_ENTITYCOMPONENT_MLENTITYCREATOR_H_