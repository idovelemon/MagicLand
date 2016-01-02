#include "MLComState.h"
#include "../marco.h"
using namespace MagicLand;

MLComState::MLComState(MLEntity* pEntity)
	:MLComponent(ML_COMTYPE_STATE, pEntity)
	,m_State(NULL)
{
}

MLComState::~MLComState()
{
	ML_SAFE_DROP(m_State);
}

void MLComState::SetState(MLState* pState)
{
	ML_SAFE_ASSERT(pState != NULL, "Can not deal with null pointer");

	if(m_State != NULL)
	{
		ML_SAFE_DROP(m_State);
	}

	m_State = pState;
	m_State->Grab();
}

MLState* MLComState::GetState() const
{
	return m_State;
}