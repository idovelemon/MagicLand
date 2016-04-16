#include "statemachine/ml_xjfallstate.h"

#include "marco.h"
#include "statemachine/ml_statemethod.h"
#include "entitycomponent/ml_com_boundbox.h"
#include "entitycomponent/ml_com_display.h"
#include "entitycomponent/ml_com_movement.h"
#include "entitycomponent/ml_com_transform.h"

using namespace magicland;

MLXJFallState::MLXJFallState()
{
}

MLXJFallState::~MLXJFallState()
{
}

void MLXJFallState::Enter(MLEntity* entity)
{
}

void MLXJFallState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with the null pointer");
	if(entity != NULL)
	{
		Fall(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLXJFallState::Exit(MLEntity* entity)
{
}

void MLXJFallState::OnCollision(MLEntity* entity)
{
	MLStateMethod::OnCollision(entity);
}

void MLXJFallState::Fall(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with the null pointer");
	if(entity != NULL)
	{
		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

		if(pTransform != NULL && pMovement != NULL)
		{
			VECTOR2 pos = pTransform->GetPos();

			VECTOR2 vel = pMovement->GetVel();
			vel.y -= pMovement->GetGravity();

			// Limit the max falling speed
			if(abs(vel.y) > pMovement->GetMaxFallSpeed())
			{
				vel.y = -pMovement->GetMaxFallSpeed();
			}

			// Handle the move left and move right
			if(GetKeyState('A') & 0x8000)
			{
				vel.x -= 3.0f;
			}
			else if(GetKeyState('D') & 0x8000)
			{
				vel.x += 3.0f;
			}

			Vec2Add(pos, pos, vel);
			pTransform->SetPos(pos.x, pos.y);

			// Ignore the x-axis of the velocity
			vel.x = 0.0f;
			pMovement->SetVel(vel.x, vel.y);
		}
	}
}