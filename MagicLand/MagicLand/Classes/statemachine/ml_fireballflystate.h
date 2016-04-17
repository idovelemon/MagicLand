//-----------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the fly state of the fire ball
//-----------------------------------------------------
#ifndef ML_STATEMAHINE_MLFIREBALLFLYSTATE_H_
#define ML_STATEMAHINE_MLFIREBALLFLYSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLFireBallFlyState:public MLState {
public:
	MLFireBallFlyState();
	virtual ~MLFireBallFlyState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLFireBallFlyState);

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	void Fly(MLEntity* entity);
	void UpdateFlyTimer(MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMAHINE_MLFIREBALLFLYSTATE_H_