#include "MLStateMachine.h"

#include "../marco.h"
#include "../EntityComponent/MLComState.h"
#include "../EntityComponent/MLEntity.h"

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

void MLStateMachine::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with the null pointer");
	if(entity != NULL)
	{
		MLComState*	pStateCom = (MLComState*)entity->GetComponent(ML_COMTYPE_STATE);

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
					if(pEntry->pConFunc(entity))
					{
						// Change the state of the entity
						pState->Exit(entity);

						ML_SAFE_ASSERT(pEntry->tailState != NULL, "");
						pEntry->tailState->Enter(entity);

						pStateCom->SetState(pEntry->tailState);

						break;
					}
				}
			}

			// Run the state
			pState = pStateCom->GetState();
			ML_SAFE_ASSERT(pState != NULL, "");
			pState->Run(entity);
		}
	}
}

void MLStateMachine::AddStateEntry(MLState* pHeadState, MLPCon pCon, MLState* pTailState)
{
	ML_SAFE_ASSERT(pHeadState != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pCon != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pTailState != NULL, "Can not deal with null pointer");
	ML_SAFE_ASSERT(pTailState != pHeadState, "Can not be the same state");
	if(pHeadState != NULL && pCon != NULL && pTailState != NULL && pTailState != pHeadState)
	{
		MLStateEntry* pEntry = new MLStateEntry;
		ML_SAFE_ASSERT(pEntry != NULL, "Allocate memory failed");
		if(pEntry != NULL)
		{
			pEntry->headState = pHeadState;
			pEntry->pConFunc = pCon;
			pEntry->tailState = pTailState;

			ML_SAFE_GRAB(pHeadState);
			ML_SAFE_GRAB(pTailState);

			m_StateTable.push_back(pEntry);
		}
	}
}