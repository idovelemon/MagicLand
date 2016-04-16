//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the end state which will be all the entities' end state
//
// Version: 2.0
// Brief: Because the end start works for every entity, so make it as a singleton instance
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLENDSTATE_H_
#define ML_STATEMACHINE_MLENDSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLEndState; };

class MagicLand::MLEndState:public MLState
{
protected:
	MLEndState();
	virtual ~MLEndState();

public:
	static MLEndState* SharedInstance();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	static MLEndState* s_Instance;
};

#endif // ML_STATEMACHINE_MLENDSTATE_H_