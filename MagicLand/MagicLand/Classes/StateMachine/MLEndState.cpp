#include "MLEndState.h"
#include "../marco.h"
using namespace MagicLand;

MLEndState* MLEndState::s_Instance = NULL;

MLEndState::MLEndState()
{
}

MLEndState::~MLEndState()
{
}

MLEndState* MLEndState::SharedInstance()
{
	if(s_Instance == NULL)
	{
		s_Instance = new MLEndState;
		ML_SAFE_ASSERT(s_Instance != NULL, "Allocate memory error");
	}

	return s_Instance;
}

void MLEndState::Enter(MLEntity* pEntity)
{
}

void MLEndState::Run(MLEntity* pEntity)
{
}

void MLEndState::Exit(MLEntity* pEntity)
{
}

void MLEndState::OnCollision(MLEntity* pEntity)
{
}