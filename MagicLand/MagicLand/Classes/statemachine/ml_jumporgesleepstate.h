//------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
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

	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLJumpOrgeSleepState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLJUMPORGESLEEPSTATE_H_