//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/31
// Version: 1.0
// Brief: This file will define the Jump state of the Hero_XJ
//------------------------------------------------------------------------
#ifndef ML_STATEMAHINE_MLXJJUMPSTATE_H_
#define ML_STATEMAHINE_MLXJJUMPSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLXJJumpState; };

class magicland::MLXJJumpState:public MLState
{
public:
	MLXJJumpState();
	virtual ~MLXJJumpState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void Jump(magicland::MLEntity* entity);
};

#endif // ML_STATEMAHINE_MLXJJUMPSTATE_H_