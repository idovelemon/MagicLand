//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the Collision system in magicland.
//------------------------------------------------------------------------
#ifndef ML_COLLISION_MLCOLLISIONMGR_H_
#define ML_COLLISION_MLCOLLISIONMGR_H_

#include <list>
#include <vector>

#include "marco.h"

namespace magicland { 

class MLEntity;

class MLCollisionMgr {

protected:
	MLCollisionMgr();
	virtual ~MLCollisionMgr();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLCollisionMgr);

public:
	static MLCollisionMgr* SharedInstance();
	static void Destroy();

public:
	void AddColEntry(magicland::MLEntity* entity);
	void RemoveColEntry(magicland::MLEntity* entity);
	void Update(float delta);
	std::vector<std::list<MLEntity*>>& GetColTable();
	unsigned int GetCVNum(); // CV for Collision Volume

protected:
	void CollisionDetect();
	void CollisionResponse();
	void ClearCollisionInfo();
	void DetectColPlayerWithEnv();
	void DetectColEnemyWithMagic();
	void DetectColEnemyWithEnv();
	void DetectColEnemyMagicWithEnv();

protected:
	typedef std::list<MLEntity*> MLColMgrList;
	typedef std::list<MLEntity*>::iterator MLColMgrListIt;
	typedef std::vector<std::list<MLEntity*>> MLColMgrTable;
	typedef std::vector<std::list<MLEntity*>>::iterator MLColMgrTableIt;

	MLColMgrTable m_ColMgrTable;

	static MLCollisionMgr* s_Instance;
};

}; // namespace magicland

#endif // ML_COLLISION_MLCOLLISIONMGR_H_