//----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 17
// Version: 1.0
// Brief: This file will define the Fly state of the Boom ball
//----------------------------------------------------------------------------
#ifndef __MLBOOMBALLFLYSTATE__H_
#define __MLBOOMBALLFLYSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLBoomBallFlyState; };

class MagicLand::MLBoomBallFlyState:public MagicLand::MLState
{
public:
	MLBoomBallFlyState();
	virtual ~MLBoomBallFlyState();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	virtual void Fly(MLEntity* entity);
};

#endif