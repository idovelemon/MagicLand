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
#ifndef ML_STATEMACHINE_MLSTARTSTATE_H_
#define ML_STATEMACHINE_MLSTARTSTATE_H_

#include "statemachine/ml_state.h"

namespace MagicLand { class MLStartState; };

class MagicLand::MLStartState:public MLState
{
protected:
	MLStartState();
	virtual ~MLStartState();

public:
	static MLStartState* SharedInstance();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	static MLStartState* s_Instance;
};

#endif // ML_STATEMACHINE_MLSTARTSTATE_H_