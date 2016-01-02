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
public:
	static bool StartOK(MagicLand::MLEntity* pEntity);
	static bool NeedJump(MagicLand::MLEntity* pEntity);
	static bool TouchGround(MagicLand::MLEntity* pEntity);
	static bool NeedFall(MagicLand::MLEntity* pEntity);
};

#endif