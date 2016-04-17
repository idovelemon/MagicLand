//------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the first state which will be all the entities's first state
//
// Version: 2.0
// Brief: Because the start state work for every entity, so make it as a singleton instance
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLSTARTSTATE_H_
#define ML_STATEMACHINE_MLSTARTSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLStartState:public MLState {
protected:
	MLStartState();
	virtual ~MLStartState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLStartState);

public:
	static MLStartState* SharedInstance();

public:
	virtual void Enter(MLEntity* entity);
	virtual void Run(MLEntity* entity);
	virtual void Exit(MLEntity* entity);
	virtual void OnCollision(MLEntity* entity);

protected:
	static MLStartState* s_Instance;
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLSTARTSTATE_H_