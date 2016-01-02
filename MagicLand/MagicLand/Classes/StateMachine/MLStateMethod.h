//----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2016/01/02
// Version: 1.0
// Brief: This file will define the state helper. There are so many helper method
// that can be used in many state
//----------------------------------------------------------------------------
#ifndef __MLSTATEMETHOD__H_
#define __MLSTATEMETHOD__H_

#include "../EntityComponent/MLEntity.h"

namespace MagicLand { class MLStateMethod; };

class MagicLand::MLStateMethod
{
public:
	static void CollisionResponse(MagicLand::MLEntity* pEntity);
	static void UpdateBoundBox(MagicLand::MLEntity* pEntity);
	static void RenderSprite(MagicLand::MLEntity* pEntity);
};

#endif