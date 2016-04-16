#include "ml_startstate.h"

#include "../marco.h"

using namespace MagicLand;

MLStartState* MLStartState::s_Instance = NULL;

MLStartState::MLStartState()
{
}

MLStartState::~MLStartState()
{
}

MLStartState* MLStartState::SharedInstance()
{
	if(s_Instance == NULL)
	{
		static MLStartState startState;
		s_Instance = &startState;
		ML_SAFE_ASSERT(s_Instance != NULL, "Allocate the memory error");
	}
	else
	{
		ML_SAFE_GRAB(s_Instance);
	}

	return s_Instance;
}

void MLStartState::Enter(MLEntity* entity)
{
}

void MLStartState::Run(MLEntity* entity)
{
}

void MLStartState::Exit(MLEntity* entity)
{
}

void MLStartState::OnCollision(MLEntity* entity)
{
}