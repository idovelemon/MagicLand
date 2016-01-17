#include "MLBoomBallFlyState.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "../Support/Script/MLScriptMgr.h"
#include "MLStateMethod.h"
using namespace MagicLand;

MLBoomBallFlyState::MLBoomBallFlyState()
{
}

MLBoomBallFlyState::~MLBoomBallFlyState()
{
}

void MLBoomBallFlyState::Enter(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
	movement->SetVel(MLScriptMgr::SharedInstance()->GetValue("BoomBallFlyVelX"), MLScriptMgr::SharedInstance()->GetValue("BoomBallFlyVelY"));
}

void MLBoomBallFlyState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	Fly(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLBoomBallFlyState::Exit(MLEntity* entity)
{
}

void MLBoomBallFlyState::OnCollision(MLEntity* entity)
{
	MLStateMethod::OnCollision(entity);
}

void MLBoomBallFlyState::Fly(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 pos = transform->GetPos();
	float rot = transform->GetRot();

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
	VECTOR2 vel = movement->GetVel();
	vel.y -= movement->GetGravity();

	if(vel.y <= -movement->GetMaxFallSpeed())
	{
		vel.y = -movement->GetMaxFallSpeed();
	}

	Vec2Add(pos, pos, vel);

	rot += MLScriptMgr::SharedInstance()->GetValue("BoomBallRotateSpeed");
	transform->SetPos(pos.x, pos.y);
	transform->SetRot(rot);
	movement->SetVel(vel.x, vel.y);
}