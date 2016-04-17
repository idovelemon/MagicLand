//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/05
// Version: 1.0
// Breif: This file will define the entity manager which will hold all the
// entities in the game.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLENTITYMGR_H_
#define ML_ENTITYCOMPONENT_MLENTITYMGR_H_

#include <map>

#include <cocos2d.h>

#include "marco.h"
#include "round/ml_room.h"
#include "support/xjmath/XJMath.h"

namespace magicland {

class MLEntity;

class MLEntityMgr {
protected:
	MLEntityMgr();
	virtual ~MLEntityMgr();
	static MLEntityMgr* s_Instance;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLEntityMgr);

public:
	static MLEntityMgr* SharedInstance();
	static void Destroy();

public:
	virtual void AddEntity(MLEntity* entity);
	virtual void Update(float delta);

	virtual MLEntity* GetPlayer();
	virtual unsigned int GetEntityNum();

protected:
	void RunLogic();
	void DestroyAllDeadEntities();

protected:
	typedef std::map<unsigned int, MLEntity*> MLEntityTable;
	typedef std::map<unsigned int, MLEntity*>::iterator MLEntityTableIt;
	MLEntityTable			m_EntityTable;
	MLEntity*				m_Player;
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLENTITYMGR_H_