//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the normal state of the hero xiaojian
//------------------------------------------------------------------------
#ifndef __MLXJNORMALSTATE__H_
#define __MLXJNORMALSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLXJNormalState; };

class MagicLand::MLXJNormalState:public MLState
{
public:
	MLXJNormalState();
	virtual ~MLXJNormalState();

public:
	virtual void Enter(MagicLand::MLEntity* pEntity);
	virtual void Run(MagicLand::MLEntity* pEntity);
	virtual void Exit(MagicLand::MLEntity* pEntity);
	virtual void OnCollision(MagicLand::MLEntity* pEntity);

protected:
	void HandleInput(MagicLand::MLEntity* pEntity);
	void Move(MagicLand::MLEntity* pEntity);
};

#endif