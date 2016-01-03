//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state which will deal with all the process
// of the specific entity in specific state.
// Version: 2.0
// Brief: Add the OnCollision interface to deal with collision response immediately after collision detection
//------------------------------------------------------------------------
#ifndef __MLSTATE__H_
#define __MLSTATE__H_

#include "../Reference/MLReference.h"
#include "../EntityComponent/MLEntity.h"

namespace MagicLand { class MLState;};

class MagicLand::MLState:public MagicLand::MLReference
{
public:
	MLState(){}
	virtual ~MLState(){}

public:
	virtual void Enter(MagicLand::MLEntity* pEntity) = 0;
	virtual void Run(MagicLand::MLEntity* pEntity) = 0;
	virtual void Exit(MagicLand::MLEntity* pEntity) = 0;
	virtual void OnCollision(MagicLand::MLEntity* pEntity) = 0;
};

#endif