//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the Collision system in MagicLand.
//------------------------------------------------------------------------
#ifndef __MLCOLLISIONMGR__H_
#define __MLCOLLISIONMGR__H_

#include "../EntityComponent/MLEntity.h"
#include <list>
#include <vector>

namespace MagicLand { class MLCollisionMgr; };

class MagicLand::MLCollisionMgr
{
protected:
	MLCollisionMgr();
	virtual ~MLCollisionMgr();

public:
	static MLCollisionMgr* SharedInstance();
	static void Destroy();

public:
	void AddColEntry(MagicLand::MLEntity* entity);
	void RemoveColEntry(MagicLand::MLEntity* entity);
	void Update(float delta);
	std::vector<std::list<MLEntity*>>& GetColTable();
	unsigned int GetCVNum(); // CV for Collision Volume

protected:
	void CollisionDetect();
	void CollisionResponse();
	void ClearCollisionInfo();
	void DetectColPlayerWithEnv();

protected:
	typedef std::list<MLEntity*> MLColMgrList;
	typedef std::list<MLEntity*>::iterator MLColMgrListIt;
	typedef std::vector<std::list<MLEntity*>> MLColMgrTable;
	typedef std::vector<std::list<MLEntity*>>::iterator MLColMgrTableIt;

	MLColMgrTable m_ColMgrTable;

	static MLCollisionMgr* s_Instance;
};

#endif