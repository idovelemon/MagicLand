//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
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

	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);
	
protected:
	virtual void Back(magicland::MLEntity* entity);

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLJumpOrgeBackState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_