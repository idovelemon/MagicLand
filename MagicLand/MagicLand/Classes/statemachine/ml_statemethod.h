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

#include "entitycomponent/ml_entity.h"

namespace magicland { class MLStateMethod; };

class magicland::MLStateMethod
{
public:
	static void CollisionResponse(magicland::MLEntity* entity);
	static void UpdateBoundBox(magicland::MLEntity* entity);
	static void RenderSprite(magicland::MLEntity* entity);
	static void OnCollision(magicland::MLEntity* entity);
	static void Fire(magicland::MLEntity* entity);
};

#endif // ML_STATEMACHINE_MLSTATEMETHOD_H_