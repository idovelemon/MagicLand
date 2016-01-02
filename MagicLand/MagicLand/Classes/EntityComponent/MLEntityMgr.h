//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define the entity manager which will hold all the
// entities in the game.
//------------------------------------------------------------------------
#ifndef __MLENTITYMGR__H_
#define __MLENTITYMGR__H_

#include <map>
#include "../Round/MLRoom.h"
#include "MLEntity.h"
#include "../Support/XJMath/XJMath.h"
#include <cocos2d.h>

namespace MagicLand {class MLEntityMgr;};

class MagicLand::MLEntityMgr
{
protected:
	MLEntityMgr();
	virtual ~MLEntityMgr();
	static MLEntityMgr* s_Instance;

public:
	static MLEntityMgr* SharedInstance();
	static void Destroy();

public:
	virtual MLEntity* AddEntity(MLEntitySubType type, int xCoord, int yCoord, MLRoom* room);
	virtual MLEntity* AddTerrianEntity(VECTOR2 min, VECTOR2 max, MLRoom* room);
	virtual void Update(float delta);

protected:
	void RunLogic();
	void DestroyAllDeadEntities();

protected:
	typedef std::map<unsigned int, MLEntity*> MLEntityTable;
	typedef std::map<unsigned int, MLEntity*>::iterator MLEntityTableIt;
	MLEntityTable			m_EntityTable;
};

#endif