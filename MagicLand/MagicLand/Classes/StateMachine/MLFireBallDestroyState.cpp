#include "MLFireBallDestroyState.h"
#include "../marco.h"
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

	entity->KillEntity();
}

void MLFireBallDestroyState::Exit(MLEntity* entity)
{
}

void MLFireBallDestroyState::OnCollision(MLEntity* entity)
{
}