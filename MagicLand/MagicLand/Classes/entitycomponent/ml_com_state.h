//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state comonent of the entity.
// It hold some information about the state of the entity.
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMPONENT_MLCOMSTATE_H_
#define ML_ENTITYCOMPONENT_MLCOMSTATE_H_

#include "marco.h"
#include "entitycomponent/ml_component.h"
#include "stateMachine/ml_state.h"

namespace magicland {

class MLComState:public MLComponent {
public:
	MLComState(magicland::MLEntity* entity);
	virtual ~MLComState();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLComState);

public:
	virtual void SetState(magicland::MLState* pState);
	virtual magicland::MLState* GetState() const;
	virtual void EnterEnd();
	virtual bool IsNeedEnd();

protected:
	magicland::MLState*	m_State;	// The state of the entity
	bool m_NeedEnd;
};

}; // namespace magicland

#endif // ML_ENTITYCOMPONENT_MLCOMSTATE_H_