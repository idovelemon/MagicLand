#include "MLStartState.h"
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
		s_Instance = new MLStartState;
		ML_SAFE_ASSERT(s_Instance != NULL, "Allocate the memory error");
	}

	return s_Instance;
}

void MLStartState::Enter(MLEntity* pEntity)
{
}

void MLStartState::Run(MLEntity* pEntity)
{
}

void MLStartState::Exit(MLEntity* pEntity)
{
}