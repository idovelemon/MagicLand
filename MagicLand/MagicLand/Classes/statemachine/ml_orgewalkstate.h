//-------------------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016 / 01 / 09
// Version: 1.0
// Brief: This file will define the Orge walk state
//-------------------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLORGEWALKSTATE_H_
#define ML_STATEMACHINE_MLORGEWALKSTATE_H_

#include "marco.h"
#include "statemachine/ml_state.h"

namespace magicland {

class MLOrgeWalkState:public MLState {
public:
	MLOrgeWalkState();
	virtual ~MLOrgeWalkState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLOrgeWalkState);

public:
	virtual void Enter(magicland::MLEntity* entity);
	virtual void Run(magicland::MLEntity* entity);
	virtual void Exit(magicland::MLEntity* entity);
	virtual void OnCollision(magicland::MLEntity* entity);

protected:
	void Walk(magicland::MLEntity* entity);
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLORGEWALKSTATE_H_