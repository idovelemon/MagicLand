//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 12
// Version: 1.0
// Brief: This file will define the Back state of the jump orge
//-----------------------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_

#include "statemachine/ml_state.h"

namespace magicland { class MLJumpOrgeBackState; };

class magicland::MLJumpOrgeBackState:public magicland::MLState
{
public:
	MLJumpOrgeBackState();
	virtual ~MLJumpOrgeBackState();

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
	
protected:
	virtual void Back(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_