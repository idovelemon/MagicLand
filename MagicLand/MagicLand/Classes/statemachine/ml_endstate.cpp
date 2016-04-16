#include "ml_endstate.h"

#include "../marco.h"
#include "../entitycomponent/ml_entity.h"

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
	else
	{
		ML_SAFE_GRAB(s_Instance);
	}

	return s_Instance;
}

void MLEndState::Enter(MLEntity* entity)
{
}

void MLEndState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		entity->KillEntity();
	}
}

void MLEndState::Exit(MLEntity* entity)
{
}

void MLEndState::OnCollision(MLEntity* entity)
{
}