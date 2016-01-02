//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/27
// Version: 1.0
// Brief: This file will define the manager that will hold all the state machine
// in the game. And if you want to use a state machine to run the entity's logic,
// you must invoke the manager's getter method to get the specific state machine.
//------------------------------------------------------------------------
#ifndef __MLSTATEMACHINEMGR__H_
#define __MLSTATEMACHINEMGR__H_

#include "../EntityComponent/MLEntity.h"
#include "MLStateMachine.h"
#include <map>

namespace MagicLand { class MLStateMachineMgr; };

class MagicLand::MLStateMachineMgr
{
protected:
	MLStateMachineMgr();
	virtual ~MLStateMachineMgr();

public:
	static MLStateMachineMgr* SharedInstance();
	static void Destroy();

public:
	//--------------------------------------------------------------------------
	// Desc:This method will add the managr node into this manager.All the manage
	// node together become the manage table of this manager.You must create this
	// manage table before you use any state machine to run the entity's logic.
	// Param:[in] type The type of entity which will run the state machine
	// Param:[in] pStateMachine The state machine that will run the entity's logic with the specific type
	//--------------------------------------------------------------------------
	virtual void AddMgrEntry(MagicLand::MLEntitySubType type, MagicLand::MLStateMachine* pStateMachine);

	//--------------------------------------------------------------------------
	// Desc: This method will run the state machine for the specific entity
	// Param:[in] pEntity The entity that need to run the state machine.
	// Warn: You must make sure the state machine with the type of this entity already exist
	//--------------------------------------------------------------------------
	virtual void RunStateMachine(MagicLand::MLEntity* pEntity);

protected:
	typedef std::map<MagicLand::MLEntitySubType, MagicLand::MLStateMachine*> MLSMMgrTable;
	typedef std::map<MagicLand::MLEntitySubType, MagicLand::MLStateMachine*>::iterator MLSMMgrTableIt;
	typedef std::pair<MagicLand::MLEntitySubType, MagicLand::MLStateMachine*> MLSMMgrPair;

	MLSMMgrTable	m_StateMachineMgrTable;

	static MLStateMachineMgr* s_Instance;
};

#endif