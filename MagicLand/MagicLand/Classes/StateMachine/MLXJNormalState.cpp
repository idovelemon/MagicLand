#include "MLXJNormalState.h"
#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComMovement.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComDisplay.h"
#include "MLStateMethod.h"
#include "../marco.h"
using namespace MagicLand;

MLXJNormalState::MLXJNormalState()
{
}

MLXJNormalState::~MLXJNormalState()
{
}

void MLXJNormalState::Enter(MLEntity* pEntity)
{
}

void MLXJNormalState::Run(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	HandleInput(pEntity);

	Move(pEntity);

	MLStateMethod::UpdateBoundBox(pEntity);

	MLStateMethod::RenderSprite(pEntity);
}

void MLXJNormalState::Exit(MLEntity* pEntity)
{
}

void MLXJNormalState::OnCollision(MLEntity* pEntity)
{
	MLStateMethod::OnCollision(pEntity);
}

void MLXJNormalState::HandleInput(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	VECTOR2 vel = MAKE_VECTOR2(0.0f, 0.0f);

	if(GetKeyState('A') & 0x8000)
	{
		vel.x -= 3.0f;
	}
	else if(GetKeyState('D') & 0x8000)
	{
		vel.x += 3.0f;
	}

	pMovement->SetVel(vel.x, vel.y);

	if(GetKeyState('J') & 0x8000)
	{
		MLStateMethod::Fire(pEntity);
	}
}

void MLXJNormalState::Move(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	VECTOR2 pos = pTransform->GetPos();
	VECTOR2 vel = pMovement->GetVel();
	VECTOR2 result;
	Vec2Add(result, pos, vel);
	pTransform->SetPos(result.x, result.y);
}