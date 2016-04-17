//-----------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 11
// Version: 1.0
// Brief: This file will define Jump orge's jump state
//-----------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGEJUMPSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGEJUMPSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLJumpOrgeJumpState:public MLState {
public:
	MLJumpOrgeJumpState();
	virtual ~MLJumpOrgeJumpState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLJumpOrgeJumpState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	virtual void Jump(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLJUMPORGEJUMPSTATE_H_