//----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define orge's wait state
//----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLORGEWAITSTATE_H_
#define ML_STATEMACHINE_MLORGEWAITSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLOrgeWaitState; };

class magicland::MLOrgeWaitState:public magicland::MLState
{
public:
	MLOrgeWaitState();
	virtual ~MLOrgeWaitState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLORGEWAITSTATE_H_