//-----------------------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 12
// Version: 1.0
// Brief: This file will define the Back state of the jump orge
//-----------------------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_
#define ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLJumpOrgeBackState; };

class MagicLand::MLJumpOrgeBackState:public MagicLand::MLState
{
public:
	MLJumpOrgeBackState();
	virtual ~MLJumpOrgeBackState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);
	
protected:
	virtual void Back(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLJUMPORGEBACKSTATE_H_