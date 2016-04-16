//-----------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the destroy state of the fireball
//-----------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_
#define ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_

#include "statemachine/ml_state.h"

namespace MagicLand { class MLFireBallDestroyState; };

class MagicLand::MLFireBallDestroyState:public MLState
{
public:
	MLFireBallDestroyState();
	virtual ~MLFireBallDestroyState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_