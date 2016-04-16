//------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 15
// Version: 1.0
// Brief: This file will define the Move state of the MovePlatform
//------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_
#define ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLMovePlatformMoveState; };

class magicland::MLMovePlatformMoveState:public magicland::MLState
{
public:
	MLMovePlatformMoveState();
	virtual ~MLMovePlatformMoveState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	virtual void Move(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_