//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/28
// Version: 1.0
// Brief: This file will define the condition that can be used for every entity
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLCOMCON_H_
#define ML_STATEMACHINE_MLCOMCON_H_

#include "marco.h"

namespace magicland {

class MLEntity;

class MLComCon {
	// Common
public:
	static bool StartOK(magicland::MLEntity* entity);
	static bool NeedEnd(magicland::MLEntity* entity);
	static bool TouchGround(magicland::MLEntity* entity);

	// For Hero
	static bool NeedJump(magicland::MLEntity* entity);
	static bool NeedFall(magicland::MLEntity* entity);

	// For FireBall
	static bool FireBallFlyTimeUp(magicland::MLEntity* entity);
	static bool FireBallCollidedWithEnemy(magicland::MLEntity* entity);

	// For Orge
	static bool OrgeWaitTimeUp(magicland::MLEntity* entity);
	static bool OrgeWalkTimeUp(magicland::MLEntity* entity);

	// For Jump Orge
	static bool JumpOrgeSeePlayer(magicland::MLEntity* entity);
	static bool JumpOrgeIsBack(magicland::MLEntity* entity);

private:
	MLComCon();
	virtual ~MLComCon();
	ML_DISALLOW_COPY_AND_ASSIGN(MLComCon);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLCOMCON_H_
