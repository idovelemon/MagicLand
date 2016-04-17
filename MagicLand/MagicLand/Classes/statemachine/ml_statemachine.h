//------------------------------------------------------------------------
// Declaration: Copyright (c),by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/21
// Version: 1.0
// Brief: This file will define the state machine which will hold all
// the process of all kind of entities.
//------------------------------------------------------------------------
#ifndef ML_STATEMACHINE_MLSTATEMACHINE_H_
#define ML_STATEMACHINE_MLSTATEMACHINE_H_

#include <vector>

#include "marco.h"
#include "statemachine/ml_con.h"
#include "statemachine/ml_state.h"
#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

class MLStateMachine:public MLReference {
public:
	MLStateMachine();
	virtual ~MLStateMachine();

private:
	ML_DISALLOW_COPY_AND_ASSIGN(MLStateMachine);

public:
	//-----------------------------------------------------------
	// Desc: This method will do the state process of the specific entity.
	// All the process of this entity will be done in this state machine
	// Param:[in] entity The entity that will run the state machine
	//-----------------------------------------------------------
	virtual void Run(magicland::MLEntity* entity);

	//-----------------------------------------------------------
	// Desc: This method will add the state entry in this state machine.
	// A state machine will deal with all entities with one type,
	// and we will use this method to build the state transform table.
	// Param:[in] pHeadState The head state of this entry
	// Param:[in] pCon If this condition is match
	//					the state of the entity will transform to tailState
	// Param:[in] pTailState The tail state of this entry
	//-----------------------------------------------------------
	virtual void AddStateEntry(magicland::MLState* pHeadState, magicland::MLPCon pCon, magicland::MLState* pTailState);

protected:
	struct MLStateEntry {
		magicland::MLState*	headState;
		magicland::MLPCon	pConFunc;
		magicland::MLState*	tailState;

		MLStateEntry()
			:headState(NULL)
			,pConFunc(0)
			,tailState(NULL) {
		}

		~MLStateEntry() {
			ML_SAFE_DROP(headState);
			pConFunc = 0;
			ML_SAFE_DROP(tailState);
		}
	};

	typedef std::vector<MLStateEntry*>	MLStateEntryArray;
	typedef std::vector<MLStateEntry*>::iterator MLStateEntryArrayIt;

	MLStateEntryArray m_StateTable;
};

}; // namespace magicland

#endif // ML_STATEMACHINE_MLSTATEMACHINE_H_