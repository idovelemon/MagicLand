//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state comonent of the entity.
// It hold some information about the state of the entity.
//------------------------------------------------------------------------
#ifndef __MLCOMSTATE__H_
#define __MLCOMSTATE__H_

#include "MLComponent.h"
#include "../StateMachine/MLState.h"

namespace MagicLand { class MLComState; };

class MagicLand::MLComState:public MLComponent
{
public:
	MLComState(MagicLand::MLEntity* pEntity);
	virtual ~MLComState();

public:
	virtual void SetState(MagicLand::MLState* pState);
	virtual MagicLand::MLState* GetState() const;

protected:
	MagicLand::MLState*	m_State;	// The state of the entity
};

#endif