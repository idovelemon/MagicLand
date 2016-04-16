//-----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 17
// Version: 1.0
// Brief: This file will define the throw orge's throw state
//-----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_
#define ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLThrowOrgeThrowState; };

class MagicLand::MLThrowOrgeThrowState:public MagicLand::MLState
{
public:
	MLThrowOrgeThrowState();
	virtual ~MLThrowOrgeThrowState();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void ThrowBoomBall(MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLTHROWORGETHROWSTATE_H_