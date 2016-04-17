//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 12
// Version: 1.0
// Brief: This file will define the Back state of the jump orge
//-----------------------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLJumpOrgeBackState:public MLState {
public:
	MLJumpOrgeBackState();
	virtual ~MLJumpOrgeBackState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLJumpOrgeBackState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
	
protected:
	virtual void Back(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_