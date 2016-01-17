//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define all the entity's creator.In this class,
// all the creator is a static method and all the creator is in a map.
// If you want to add new entity, you must add a new creator in this map
//------------------------------------------------------------------------
#ifndef __MLENTITYCREATOR__H_
#define __MLENTITYCREATOR__H_

#include "MLEntity.h"
#include "../Round/MLRoom.h"
#include <cocos2d.h>

namespace MagicLand 
{
	class MLEntityCreator;
	struct MLETYCreatorEntry;
};

typedef MagicLand::MLEntity* (*PFUNCEntityCreator)(int xCoord, int yCoord, MagicLand::MLRoom* room);

struct MagicLand::MLETYCreatorEntry
{
	MLEntitySubType type;
	PFUNCEntityCreator creator;
};

class MagicLand::MLEntityCreator
{
protected:
	static MLETYCreatorEntry s_CreatorTable[];

public:
	static MLEntity* CreateTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room);
	static MLEntity* CreateFireBall(float posx, float posy, MagicLand::MLDir dir, MLRoom* room);
	static MLEntity* CreateOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateJumpOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateMovePlatform(float posx, float posy, MLRoom* room);
	static MLEntity* CreateThrowOrge(float posx, float posy, MLRoom* room);
	static MLEntity* CreateBoomBall(float posx, float posy, MLRoom* room);

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
};
#endif