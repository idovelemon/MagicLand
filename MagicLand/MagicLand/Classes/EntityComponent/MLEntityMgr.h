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

#include "../Round/MLRoom.h"
#include "../Support/XJMath/XJMath.h"

namespace MagicLand 
{
	class MLEntityMgr;
	class MLEntity;
};

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

#endif // ML_ENTITYCOMPONENT_MLENTITYMGR_H_