#include "statemachine/ml_fireballdestroystate.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"

using namespace MagicLand;

MLFireBallDestroyState::MLFireBallDestroyState()
{
}

MLFireBallDestroyState::~MLFireBallDestroyState()
{
}

void MLFireBallDestroyState::Enter(MLEntity* entity)
{
}

void MLFireBallDestroyState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with empty entity");

	MLComState* state = (MLComState*)entity->GetComponent(ML_COMTYPE_STATE);
	ML_SAFE_ASSERT(state != NULL, "Please make sure the State component exist");

	if(entity != NULL && state != NULL)
	{
		state->EnterEnd();
	}
}

void MLFireBallDestroyState::Exit(MLEntity* entity)
{
}

void MLFireBallDestroyState::OnCollision(MLEntity* entity)
{
}