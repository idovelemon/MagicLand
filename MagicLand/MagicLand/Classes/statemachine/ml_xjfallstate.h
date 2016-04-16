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

namespace MagicLand { class MLXJFallState; };

class MagicLand::MLXJFallState:public MLState
{
public:
	MLXJFallState();
	virtual ~MLXJFallState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	void Fall(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLXJFALLSTATE_H_