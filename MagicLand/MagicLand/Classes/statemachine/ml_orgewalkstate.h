//-------------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the Orge walk state
//-------------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLORGEWALKSTATE_H_
#define ML_STATEMACHINE_MLORGEWALKSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLOrgeWalkState; };

class magicland::MLOrgeWalkState:public MLState
{
public:
	MLOrgeWalkState();
	virtual ~MLOrgeWalkState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void Walk(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLORGEWALKSTATE_H_