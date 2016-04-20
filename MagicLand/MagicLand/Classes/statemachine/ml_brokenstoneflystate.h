//--------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 18
// Version: 1.0
// Brief: This file will define the fly state of the broken stone
//--------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_
#define ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLBrokenStoneFlyState:public MLState {
public:
	MLBrokenStoneFlyState();
	virtual ~MLBrokenStoneFlyState();

	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void Fly(MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLBrokenStoneFlyState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_