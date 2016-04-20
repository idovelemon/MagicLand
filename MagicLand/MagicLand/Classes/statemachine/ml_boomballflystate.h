//----------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 17
// Version: 1.0
// Brief: This file will define the Fly state of the Boom ball
//----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLBOOMBALLFLYSTATE_H_
#define ML_STATEMACHINE_MLBOOMBALLFLYSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLBoomBallFlyState:public MLState {
public:
	MLBoomBallFlyState();
	virtual ~MLBoomBallFlyState();

	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void Fly(MLEntity* entity);
	virtual void Boom(MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLBoomBallFlyState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLBOOMBALLFLYSTATE_H_