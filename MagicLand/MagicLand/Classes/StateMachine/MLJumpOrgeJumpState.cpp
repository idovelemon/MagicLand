#include "MLJumpOrgeJumpState.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "../EntityComponent/MLEntityMgr.h"
#include "../Support/Script/MLScriptMgr.h"
#include "MLStateMethod.h"
using namespace MagicLand;

MLJumpOrgeJumpState::MLJumpOrgeJumpState()
{
}

MLJumpOrgeJumpState::~MLJumpOrgeJumpState()
{
}

void MLJumpOrgeJumpState::Enter(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");

	MLEntity* player = MLEntityMgr::SharedInstance()->GetPlayer();
	ML_SAFE_ASSERT(player != NULL, "Please make sure the player is not empty");

	MLComTransform* playerTransform = (MLComTransform*)player->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(playerTransform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 playerPos = playerTransform->GetPos();

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 pos = transform->GetPos();

	float moveSpeed = 0.0f, jumpSpeed = 0.0f;
	ML_SCRIPT_GETVALUE(moveSpeed, "JumpOrgeMoveSpeed");
	ML_SCRIPT_GETVALUE(jumpSpeed, "JumpOrgeJumpSpeed");
	if(playerPos.x < pos.x) // Player is at the right of the JumpOrge
	{
		movement->SetVel(-moveSpeed, jumpSpeed);
	}
	else					// Player is at the left of the JumpOrge
	{
		movement->SetVel(moveSpeed, jumpSpeed);
	}
}

void MLJumpOrgeJumpState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	Jump(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLJumpOrgeJumpState::Exit(MLEntity* entity)
{
}

void MLJumpOrgeJumpState::OnCollision(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLStateMethod::OnCollision(entity);
}

void MLJumpOrgeJumpState::Jump(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "There is no movement component");

	VECTOR2 vel = movement->GetVel();
	vel.y -= movement->GetGravity();
	if(vel.y < -movement->GetMaxFallSpeed())
	{
		vel.y = -movement->GetMaxFallSpeed();
	}
	movement->SetVel(vel.x, vel.y);

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "There is no transform component");

	VECTOR2 pos = transform->GetPos();
	Vec2Add(pos, pos, vel);

	transform->SetPos(pos.x, pos.y);
}