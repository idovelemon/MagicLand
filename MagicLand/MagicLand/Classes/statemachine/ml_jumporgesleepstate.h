//------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 11
// Version: 1.0
// Brief: This file will define the Jump orge's sleep state
//------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLJumpOrgeSleepState:public MLState {
public:
	MLJumpOrgeSleepState();
	virtual ~MLJumpOrgeSleepState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLJumpOrgeSleepState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_