#include "MLFireBallFlyState.h"
#include "../marco.h"
#include "MLStateMethod.h"
#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComMovement.h"
using namespace MagicLand;

MLFireBallFlyState::MLFireBallFlyState()
{
}

MLFireBallFlyState::~MLFireBallFlyState()
{
}

void MLFireBallFlyState::Enter(MLEntity* entity)
{
}

void MLFireBallFlyState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");

	Fly(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLFireBallFlyState::Exit(MLEntity* entity)
{
}

void MLFireBallFlyState::OnCollision(MLEntity* entity)
{
}

void MLFireBallFlyState::Fly(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with empty entity");

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "There is no transform component");

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "There is no movement component");

	VECTOR2 pos = transform->GetPos();
	VECTOR2 vel = movement->GetVel();
	Vec2Add(pos, pos, vel);
	transform->SetPos(pos.x, pos.y);
}