//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2016/01/01
// Version: 1.0
// Brief: This file will define the falling state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLXJFALLSTATE_H_
#define ML_STATEMACHINE_MLXJFALLSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLXJFallState; };

class magicland::MLXJFallState:public MLState
{
public:
	MLXJFallState();
	virtual ~MLXJFallState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void Fall(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLXJFALLSTATE_H_