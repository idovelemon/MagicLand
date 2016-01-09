//-----------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2016. All right reserved.
// Author: xiaojian
// Date: 2016 / 01 / 06
// Version: 1.0
// Brief: This file will define the fly state of the fire ball
//-----------------------------------------------------
#ifndef __MLFIREBALLFLYSTATE__H_
#define __MLFIREBALLFLYSTATE__H_

#include "MLState.h"

namespace MagicLand { class MLFireBallFlyState; };

class MagicLand::MLFireBallFlyState:public MLState
{
public:
	MLFireBallFlyState();
	virtual ~MLFireBallFlyState();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	void Fly(MLEntity* entity);
	void UpdateFlyTimer(MLEntity* entity);
};

#endif