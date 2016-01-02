#include "MLStateMachine.h"
#include "../marco.h"
#include "../EntityComponent/MLComState.h"
using namespace MagicLand;

MLStateMachine::MLStateMachine()
{
	m_StateTable.clear();
}

MLStateMachine::~MLStateMachine()
{	
	for(MLStateEntryArrayIt it = m_StateTable.begin() ;it != m_StateTable.end(); ++it)
	{
		MLStateEntry* pEntry = *it;
		ML_SAFE_DELETE(pEntry);
	}
}

void MLStateMachine::Run(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with the null pointer");

	MLComState*	pStateCom = (MLComState*)pEntity->GetComponent(ML_COMTYPE_STATE);

	if(pStateCom != NULL) // If the state component exist
	{
		MLState* pState = pStateCom->GetState();
		ML_SAFE_ASSERT(pState != NULL, "");

		// Check if we need to transform to another state
		for(MLStateEntryArrayIt it = m_StateTable.begin() ;it != m_StateTable.end(); ++it)
		{
			MLStateEntry* pEntry = *it;
			ML_SAFE_ASSERT(pEntry != NULL, "");

			if(pEntry->headState == pState)
			{
				if(pEntry->pConFunc(pEntity))
				{
					// Change the state of the entity
					pState->Exit(pEntity);

					ML_SAFE_ASSERT(pEntry->tailState != NULL, "");
					pEntry->tailState->Enter(pEntity);

					pStateCom->SetState(pEntry->tailState);

					break;
				}
			}
		}

		// Run the state
		pState = pStateCom->GetState();
		ML_SAFE_ASSERT(pState != NULL, "");
		pState->Run(pEntity);
	}
}

void MLStateMachine::AddStateEntry(MLState* pHeadState, MLPCon pCon, MLState* pTailState)
{
	ML_SAFE_ASSERT(pHeadState != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pCon != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pTailState != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pTailState != pHeadState, "Can not be the same state");
	
	MLStateEntry* pEntry = new MLStateEntry;
	ML_SAFE_ASSERT(pEntry != NULL, "Allocate memory failed");
	pEntry->headState = pHeadState;
	pEntry->pConFunc = pCon;
	pEntry->tailState = pTailState;

	m_StateTable.push_back(pEntry);
}