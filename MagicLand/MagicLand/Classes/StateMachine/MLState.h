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

namespace MagicLand
{
	class MLState;
	class MLEntity;
};

class MagicLand::MLState:public MagicLand::MLReference
{
public:
	MLState(){}
	virtual ~MLState(){}

public:
	virtual void Enter(MagicLand::MLEntity* entity) = 0;
	virtual void Run(MagicLand::MLEntity* entity) = 0;
	virtual void Exit(MagicLand::MLEntity* entity) = 0;
	virtual void OnCollision(MagicLand::MLEntity* entity) = 0;
};

#endif // __MLSTATE__H_