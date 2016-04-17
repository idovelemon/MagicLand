//--------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/28
// Version: 1.0
// Brief: This file will define the condition that will be used in the game
//--------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLCON_H_
#define ML_STATEMACHINE_MLCON_H_

#include "entitycomponent/ml_entity.h"

namespace magicland {
	typedef bool (*MLPCon)(magicland::MLEntity* entity);
} // namespace magicland

#endif // ML_STATEMACHINE_MLCON_H_