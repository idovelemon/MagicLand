//------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 15
// Version: 1.0
// Brief: This file will define the Move state of the MovePlatform
//------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_
#define ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_

#include "MLState.h"

namespace MagicLand { class MLMovePlatformMoveState; };

class MagicLand::MLMovePlatformMoveState:public MagicLand::MLState
{
public:
	MLMovePlatformMoveState();
	virtual ~MLMovePlatformMoveState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	virtual void Move(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLMOVEPLATFORMMOVESTATE_H_