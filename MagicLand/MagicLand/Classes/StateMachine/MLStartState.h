//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the first state which will be all the entities's first state
//
// Version: 2.0
// Brief: Because the start state work for every entity, so make it as a singleton instance
//------------------------------------------------------------------------
#ifndef __MLSTARTSTATE__H_
#define __MLSTARTSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLStartState; };

class MagicLand::MLStartState:public MLState
{
protected:
	MLStartState();
	virtual ~MLStartState();

public:
	static MLStartState* SharedInstance();

public:
	virtual void Enter(MLEntity* pEntity);
	virtual void Run(MLEntity* pEntity);
	virtual void Exit(MLEntity* pEntity);
	virtual void OnCollision(MLEntity* pEntity);

protected:
	static MLStartState* s_Instance;
};

#endif