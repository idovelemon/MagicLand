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
	// For Hero
public:
	static bool StartOK(MagicLand::MLEntity* entity);
	static bool NeedJump(MagicLand::MLEntity* entity);
	static bool TouchGround(MagicLand::MLEntity* entity);
	static bool NeedFall(MagicLand::MLEntity* entity);

	// For FireBall
public:
	static bool FlyTimeUp(MagicLand::MLEntity* entity);
};

#endif
