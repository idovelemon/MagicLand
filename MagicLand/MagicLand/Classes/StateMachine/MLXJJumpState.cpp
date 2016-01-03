#include "MLXJJumpState.h"
#include "../marco.h"
#include "../EntityComponent/MLComMovement.h"
#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComDisplay.h"
#include "MLStateMethod.h"

using namespace MagicLand;

MLXJJumpState::MLXJJumpState()
{
}

MLXJJumpState::~MLXJJumpState()
{
}

void MLXJJumpState::Enter(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with null pointer");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	VECTOR2 vel = pMovement->GetVel();
	vel.y += 20.0f;
	pMovement->SetVel(vel.x, vel.y);
}

void MLXJJumpState::Run(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with null pointer");

	Jump(pEntity);

	MLStateMethod::UpdateBoundBox(pEntity);

	MLStateMethod::RenderSprite(pEntity);
}

void MLXJJumpState::Exit(MLEntity* pEntity)
{
}

void MLXJJumpState::OnCollision(MLEntity* pEntity)
{
	MLStateMethod::OnCollision(pEntity);
}

void MLXJJumpState::Jump(MagicLand::MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with null pointer");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	VECTOR2 vel = pMovement->GetVel();

	if(GetKeyState('A') & 0x8000)
	{
		vel.x -= 3.0f;
	}
	else if(GetKeyState('D') & 0x8000)
	{
		vel.x += 3.0f;
	}

	vel.y -= pMovement->GetGravity();

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	VECTOR2 pos = pTransform->GetPos();
	Vec2Add(pos, pos, vel);

	pTransform->SetPos(pos.x, pos.y);

	// Only save the y-axis of the velocity
	pMovement->SetVel(0.0f, vel.y);
}