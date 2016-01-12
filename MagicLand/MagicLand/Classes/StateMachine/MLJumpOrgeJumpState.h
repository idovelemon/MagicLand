//-----------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 11
// Version: 1.0
// Brief: This file will define Jump orge's jump state
//-----------------------------------------------------------------
#ifndef __MLJUMPORGEJUMPSTATE__H_
#define __MLJUMPORGEJUMPSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLJumpOrgeJumpState; };

class MagicLand::MLJumpOrgeJumpState:public MLState
{
public:
	MLJumpOrgeJumpState();
	virtual ~MLJumpOrgeJumpState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	virtual void Jump(MagicLand::MLEntity* entity);
};

#endif