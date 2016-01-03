#include "MLXJFallState.h"
#include "../marco.h"

#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComMovement.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComDisplay.h"

#include "MLStateMethod.h"

using namespace MagicLand;

MLXJFallState::MLXJFallState()
{
}

MLXJFallState::~MLXJFallState()
{
}

void MLXJFallState::Enter(MLEntity* pEntity)
{
}

void MLXJFallState::Run(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with the null pointer");

	Fall(pEntity);

	MLStateMethod::UpdateBoundBox(pEntity);

	MLStateMethod::RenderSprite(pEntity);
}

void MLXJFallState::Exit(MLEntity* pEntity)
{
}

void MLXJFallState::OnCollision(MLEntity* pEntity)
{
	MLStateMethod::OnCollision(pEntity);
}

void MLXJFallState::Fall(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	VECTOR2 pos = pTransform->GetPos();

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

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