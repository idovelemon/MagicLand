//------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 11
// Version: 1.0
// Brief: This file will define the Jump orge's sleep state
//------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_

#include "ml_state.h"

namespace MagicLand { class MLJumpOrgeSleepState; };

class MagicLand::MLJumpOrgeSleepState:public MagicLand::MLState
{
public:
	MLJumpOrgeSleepState();
	virtual ~MLJumpOrgeSleepState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_