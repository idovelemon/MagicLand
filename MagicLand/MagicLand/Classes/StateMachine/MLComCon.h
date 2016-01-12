//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/28
// Version: 1.0
// Brief: This file will define the condition that can be used for every entity
//------------------------------------------------------------------------
#ifndef __MLCOMCON__H_
#define __MLCOMCON__H_

#include "MLCon.h"

namespace MagicLand { class MLComCon; };

class MagicLand::MLComCon
{
	// Common
public:
	static bool StartOK(MagicLand::MLEntity* entity);
	static bool NeedEnd(MagicLand::MLEntity* entity);

	// For Hero
public:
	static bool NeedJump(MagicLand::MLEntity* entity);
	static bool TouchGround(MagicLand::MLEntity* entity);
	static bool NeedFall(MagicLand::MLEntity* entity);

	// For FireBall
public:
	static bool FireBallFlyTimeUp(MagicLand::MLEntity* entity);
	static bool FireBallCollidedWithEnemy(MagicLand::MLEntity* entity);

	// For Orge
public:
	static bool OrgeWaitTimeUp(MagicLand::MLEntity* entity);
	static bool OrgeWalkTimeUp(MagicLand::MLEntity* entity);

	// For Jump Orge
public:
	static bool JumpOrgeSeePlayer(MagicLand::MLEntity* entity);

};

#endif
