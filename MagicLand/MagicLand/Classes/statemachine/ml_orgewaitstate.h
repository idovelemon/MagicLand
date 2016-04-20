//----------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define orge's wait state
//----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLORGEWAITSTATE_H_
#define ML_STATEMACHINE_MLORGEWAITSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLOrgeWaitState:public MLState {
public:
	MLOrgeWaitState();
	virtual ~MLOrgeWaitState();

	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLOrgeWaitState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLORGEWAITSTATE_H_