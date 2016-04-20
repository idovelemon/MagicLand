//-----------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the destroy state of the fireball
//-----------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_
#define ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLFireBallDestroyState:public MLState
{
public:
	MLFireBallDestroyState();
	virtual ~MLFireBallDestroyState();

	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLFireBallDestroyState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLFIREBALLDESTROYSTATE_H_