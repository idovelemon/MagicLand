//----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define orge's wait state
//----------------------------------------------------------------------------
#ifndef __MLORGEWAITSTATE__H_
#define __MLORGEWAITSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLOrgeWaitState; };

class MagicLand::MLOrgeWaitState:public MagicLand::MLState
{
public:
	MLOrgeWaitState();
	virtual ~MLOrgeWaitState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);
};

#endif