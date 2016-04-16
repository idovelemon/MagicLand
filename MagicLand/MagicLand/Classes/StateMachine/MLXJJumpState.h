//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/31
// Version: 1.0
// Brief: This file will define the Jump state of the Hero_XJ
//------------------------------------------------------------------------
#ifndef ML_STATEMAHINE_MLXJJUMPSTATE_H_
#define ML_STATEMAHINE_MLXJJUMPSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLXJJumpState; };

class MagicLand::MLXJJumpState:public MLState
{
public:
	MLXJJumpState();
	virtual ~MLXJJumpState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	void Jump(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMAHINE_MLXJJUMPSTATE_H_