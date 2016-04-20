//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the end state which will be all the entities' end state
//
// Version: 2.0
// Brief: Because the end start works for every entity, so make it as a singleton instance
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLENDSTATE_H_
#define ML_STATEMACHINE_MLENDSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {
	 
class MLEndState:public MLState
{
public:
	static MLEndState* SharedInstance();

	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
  MLEndState();
	virtual ~MLEndState();

	static MLEndState* s_Instance;

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLEndState);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLENDSTATE_H_