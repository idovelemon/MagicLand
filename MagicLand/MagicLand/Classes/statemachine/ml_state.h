//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state which will deal with all the process
// of the specific entity in specific state.
// Version: 2.0
// Brief: Add the OnCollision interface to deal with collision response immediately after collision detection
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLSTATE_H_
#define ML_STATEMACHINE_MLSTATE_H_

#include "marco.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

class MLState:public MLReference {
public:
	MLState(){}
	virtual ~MLState(){}

public:
	virtual void Enter(magicland::MLEntity* entity) = 0;
	virtual void Run(magicland::MLEntity* entity) = 0;
	virtual void Exit(magicland::MLEntity* entity) = 0;
	virtual void OnCollision(magicland::MLEntity* entity) = 0;

private:
  ML_DISALLOW_COPY_AND_ASSIGN(MLState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLSTATE_H_