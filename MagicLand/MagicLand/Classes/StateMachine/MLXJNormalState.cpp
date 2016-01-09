#include "MLXJNormalState.h"
#include "../EntityComponent/MLAllComs.h"
#include "../Framerate/MLFrameRateMgr.h"
#include "MLStateMethod.h"
#include "../marco.h"
using namespace MagicLand;

MLXJNormalState::MLXJNormalState()
{
}

MLXJNormalState::~MLXJNormalState()
{
}

void MLXJNormalState::Enter(MLEntity* entity)
{
}

void MLXJNormalState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	HandleInput(entity);

	Move(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLXJNormalState::Exit(MLEntity* entity)
{
}

void MLXJNormalState::OnCollision(MLEntity* entity)
{
	MLStateMethod::OnCollision(entity);
}

void MLXJNormalState::HandleInput(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(dir != NULL, "There is no Dir component");

	VECTOR2 vel = MAKE_VECTOR2(0.0f, 0.0f);

	if(GetKeyState('A') & 0x8000)
	{
		vel.x -= 3.0f;
		dir->SetDir(ML_DIR_LEFT);
	}
	else if(GetKeyState('D') & 0x8000)
	{
		vel.x += 3.0f;
		dir->SetDir(ML_DIR_RIGHT);
	}

	pMovement->SetVel(vel.x, vel.y);

	static bool bPress = false;
	static float curFrame = 0.0f;
	if((GetKeyState('J') & 0x8000) && bPress == false)
	{
		MLStateMethod::Fire(entity);
		bPress = true;
	}

	if(bPress == true)
	{
		curFrame += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
		if(curFrame > 0.5f)
		{
			curFrame = 0.0f;
			bPress = false;
		}
	}
}

void MLXJNormalState::Move(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	VECTOR2 pos = pTransform->GetPos();
	VECTOR2 vel = pMovement->GetVel();
	VECTOR2 result;
	Vec2Add(result, pos, vel);
	pTransform->SetPos(result.x, result.y);
}