//-----------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 17
// Version: 1.0
// Brief: This file will define the throw orge's throw state
//-----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_
#define ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLThrowOrgeThrowState:public MLState {
public:
	MLThrowOrgeThrowState();
	virtual ~MLThrowOrgeThrowState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLThrowOrgeThrowState);

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void ThrowBoomBall(MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_