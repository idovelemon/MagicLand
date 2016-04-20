//----------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016/01/02
// Version: 1.0
// Brief: This file will define the state helper. There are so many helper method
// that can be used in many state
//----------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLSTATEMETHOD_H_
#define ML_STATEMACHINE_MLSTATEMETHOD_H_

#include "marco.h"
#include "entitycomponent/ml_entity.h"

namespace magicland {

class MLStateMethod {
public:
	static void CollisionResponse(magicland::MLEntity* entity);
	static void UpdateBoundBox(magicland::MLEntity* entity);
	static void RenderSprite(magicland::MLEntity* entity);
	static void OnCollision(magicland::MLEntity* entity);
	static void Fire(magicland::MLEntity* entity);

private:
	MLStateMethod();
	virtual ~MLStateMethod();
	ML_DISALLOW_COPY_AND_ASSIGN(MLStateMethod);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLSTATEMETHOD_H_