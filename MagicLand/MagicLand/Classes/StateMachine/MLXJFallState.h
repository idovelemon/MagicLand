//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2016/01/01
// Version: 1.0
// Brief: This file will define the falling state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef __MLXJFALLSTATE__H_
#define __MLXJFALLSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLXJFallState; };

class MagicLand::MLXJFallState:public MLState
{
public:
	MLXJFallState();
	virtual ~MLXJFallState();

public:
	virtual void Enter(MagicLand::MLEntity* pEntity);
	virtual void Run(MagicLand::MLEntity* pEntity);
	virtual void Exit(MagicLand::MLEntity* pEntity);

protected:
	void Fall(MagicLand::MLEntity* pEntity);
};

#endif