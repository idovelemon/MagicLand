//-------------------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the Orge walk state
//-------------------------------------------------------------------------------------
#ifndef __MLORGEWALKSTATE__H_
#define __MLORGEWALKSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLOrgeWalkState; };

class MagicLand::MLOrgeWalkState:public MLState
{
public:
	MLOrgeWalkState();
	virtual ~MLOrgeWalkState();

public:
	virtual void Enter(MagicLand::MLEntity* entity);
	virtual void Run(MagicLand::MLEntity* entity);
	virtual void Exit(MagicLand::MLEntity* entity);
	virtual void OnCollision(MagicLand::MLEntity* entity);

protected:
	void Walk(MagicLand::MLEntity* entity);
};

#endif