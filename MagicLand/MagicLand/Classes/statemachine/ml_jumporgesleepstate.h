//------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 11
// Version: 1.0
// Brief: This file will define the Jump orge's sleep state
//------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLJumpOrgeSleepState; };

class magicland::MLJumpOrgeSleepState:public magicland::MLState
{
public:
	MLJumpOrgeSleepState();
	virtual ~MLJumpOrgeSleepState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_