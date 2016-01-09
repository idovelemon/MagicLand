#include "MLComState.h"
#include "../marco.h"
using namespace MagicLand;

MLComState::MLComState(MLEntity* entity)
	:MLComponent(ML_COMTYPE_STATE, entity)
	,m_State(NULL)
	,m_NeedEnd(false)
{
}

MLComState::~MLComState()
{
	ML_SAFE_DROP(m_State);
}

void MLComState::SetState(MLState* pState)
{
	ML_SAFE_ASSERT(pState != NULL, "Can not deal with null pointer");

	ML_SAFE_DROP(m_State);

	m_State = pState;
	ML_SAFE_GRAB(m_State);
}

MLState* MLComState::GetState() const
{
	return m_State;
}

void MLComState::EnterEnd()
{
	m_NeedEnd = true;
}

bool MLComState::IsNeedEnd()
{
	return m_NeedEnd;
}