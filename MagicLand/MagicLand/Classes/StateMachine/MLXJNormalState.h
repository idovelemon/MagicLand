//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the normal state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLXJNORMALSTATE_H_
#define ML_STATEMACHINE_MLXJNORMALSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLXJNormalState; };

class MagicLand::MLXJNormalState:public MLState
{
public:
	MLXJNormalState();
	virtual ~MLXJNormalState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	void HandleInput(MagicLand::MLEntity* entity);
	void Move(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLXJNORMALSTATE_H_