#include "MLStateMachineMgr.h"
#include "../marco.h"
#include <Windows.h>

using namespace MagicLand;

MLStateMachineMgr* MLStateMachineMgr::s_Instance = NULL;

MLStateMachineMgr::MLStateMachineMgr()
{
	m_StateMachineMgrTable.clear();
}

MLStateMachineMgr::~MLStateMachineMgr()
{
	for(MLSMMgrTableIt it = m_StateMachineMgrTable.begin(); it != m_StateMachineMgrTable.end(); ++it)
	{
		MLStateMachine* pStateMachine = it->second;
		ML_SAFE_ASSERT(pStateMachine != NULL, "There is a error in this manager");
		ML_SAFE_DROP(pStateMachine);
	}

	m_StateMachineMgrTable.clear();
}

MLStateMachineMgr* MLStateMachineMgr::SharedInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new MLStateMachineMgr();
		ML_SAFE_ASSERT(s_Instance != NULL, "Create the MLStateMachineMgr Error");
	}

	return s_Instance;
}

void MLStateMachineMgr::Destroy()
{
	ML_SAFE_DELETE(s_Instance);
}

void MLStateMachineMgr::AddMgrEntry(MLEntitySubType type, MLStateMachine* pStateMachine)
{
	ML_SAFE_ASSERT(ML_ETYSUBTYPE_NONE < type && type < ML_ETYSUBTYPE_TOTAL, "Please make sure the type exist");
	ML_SAFE_ASSERT(pStateMachine != NULL, "Please pass a valid state machine pointer");

	if(m_StateMachineMgrTable.find(type) != m_StateMachineMgrTable.end())
	{
		ML_SAFE_ASSERT(false, "Can not add the same type of entity more than once");
	}

	m_StateMachineMgrTable.insert(MLSMMgrPair(type, pStateMachine));
	pStateMachine->Grab(); // Add the reference count
}

void MLStateMachineMgr::RunStateMachine(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Entity can not be null");
	MLSMMgrTableIt it = m_StateMachineMgrTable.find(pEntity->GetSubType());

	if(it != m_StateMachineMgrTable.end())
	{
		MLStateMachine* pStateMachine = it->second;
		ML_SAFE_ASSERT(pStateMachine != NULL, "Please pass a valid state machine pointer");
		pStateMachine->Run(pEntity);
	}
	else
	{
		if(pEntity->GetSubType() != ML_ETYSUBTYPE_WALL
			&& pEntity->GetSubType() != ML_ETYSUBTYPE_TERRIAN)
		{
			ML_SAFE_ASSERT(false, "Can not find the state machine for this type of entity");
		}
	}
}