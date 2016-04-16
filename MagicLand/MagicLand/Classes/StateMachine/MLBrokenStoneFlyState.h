//--------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 18
// Version: 1.0
// Brief: This file will define the fly state of the broken stone
//--------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_
#define ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_

#include "MLState.h"

namespace MagicLand { class MLBrokenStoneFlyState; };

class MagicLand::MLBrokenStoneFlyState:public MLState
{
public:
	MLBrokenStoneFlyState();
	virtual ~MLBrokenStoneFlyState();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void Fly(MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLBROKENSTONEFLYSTATE_H_