//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the normal state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLXJNORMALSTATE_H_
#define ML_STATEMACHINE_MLXJNORMALSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLXJNormalState:public MLState {
public:
	MLXJNormalState();
	virtual ~MLXJNormalState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLXJNormalState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void HandleInput(magicland::MLEntity* entity);
	void Move(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLXJNORMALSTATE_H_