//----------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2016/01/02
// Version: 1.0
// Brief: This file will define the state helper. There are so many helper method
// that can be used in many state
//----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLSTATEMETHOD_H_
#define ML_STATEMACHINE_MLSTATEMETHOD_H_

#include "../EntityComponent/MLEntity.h"

namespace MagicLand { class MLStateMethod; };

class MagicLand::MLStateMethod
{
public:
	static void CollisionResponse(MagicLand::MLEntity* entity);
	static void UpdateBoundBox(MagicLand::MLEntity* entity);
	static void RenderSprite(MagicLand::MLEntity* entity);
	static void OnCollision(MagicLand::MLEntity* entity);
	static void Fire(MagicLand::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLSTATEMETHOD_H_