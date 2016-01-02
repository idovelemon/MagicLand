//------------------------------------------------------------------------
// Declaration: Copyright (c),by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state machine which will hold all
// the process of all kind of entities.
//------------------------------------------------------------------------
#ifndef __MLSTATEMACHINE__H_
#define __MLSTATEMACHINE__H_

#include "../Reference/MLReference.h"
#include "../EntityComponent/MLEntity.h"
#include "MLState.h"
#include "MLCon.h"
#include <vector>

namespace MagicLand { class MLStateMachine;};

class MagicLand::MLStateMachine:public MagicLand::MLReference
{
public:
	MLStateMachine();
	virtual ~MLStateMachine();

public:
	//-----------------------------------------------------------
	// Desc: This method will do the state process of the specific entity.
	// All the process of this entity will be done in this state machine
	// Param:[in] pEntity The entity that will run the state machine
	//-----------------------------------------------------------
	virtual void Run(MagicLand::MLEntity* pEntity);

	//-----------------------------------------------------------
	// Desc: This method will add the state entry in this state machine.
	// A state machine will deal with all entities with one type,
	// and we will use this method to build the state transform table.
	// Param:[in] pHeadState The head state of this entry
	// Param:[in] pCon If this condition is match
	//					the state of the entity will transform to tailState
	// Param:[in] pTailState The tail state of this entry
	//-----------------------------------------------------------
	virtual void AddStateEntry(MagicLand::MLState* pHeadState, MagicLand::MLPCon pCon, MagicLand::MLState* pTailState);

protected:
	struct MLStateEntry
	{
		MagicLand::MLState*	headState;
		MagicLand::MLPCon	pConFunc;
		MagicLand::MLState*	tailState;
	};

	typedef std::vector<MLStateEntry*>	MLStateEntryArray;
	typedef std::vector<MLStateEntry*>::iterator MLStateEntryArrayIt;

	MLStateEntryArray m_StateTable;
};

#endif