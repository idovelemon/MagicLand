//--------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
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