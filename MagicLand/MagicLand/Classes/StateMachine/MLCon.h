//--------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/28
// Version: 1.0
// Brief: This file will define the condition that will be used in the game
//--------------------------------------------------------------------------
#ifndef __MLCON__H_
#define __MLCON__H_

#include "../EntityComponent/MLEntity.h"

namespace MagicLand
{
	typedef bool (*MLPCon)(MagicLand::MLEntity* entity);
}

#endif