//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016/01/01
// Version: 1.0
// Brief: This file will define the falling state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLXJFALLSTATE_H_
#define ML_STATEMACHINE_MLXJFALLSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLXJFallState:public MLState {
public:
	MLXJFallState();
	virtual ~MLXJFallState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLXJFallState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void Fall(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLXJFALLSTATE_H_