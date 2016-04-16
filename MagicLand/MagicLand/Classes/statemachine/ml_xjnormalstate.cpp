#include "ml_xjnormalstate.h"

#include "../marco.h"
#include "ml_statemethod.h"
#include "../entitycomponent/ml_allcoms.h"
#include "../framerate/ml_frameratemgr.h"
#include "../support/script/ml_scriptmgr.h"

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
	if(entity != NULL)
	{
		HandleInput(entity);

		Move(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
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
	if(entity != NULL)
	{
		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

		MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
		ML_SAFE_ASSERT(dir != NULL, "There is no Dir component");

		if(pTransform != NULL && pMovement != NULL && dir != NULL)
		{
			VECTOR2 vel = MAKE_VECTOR2(0.0f, 0.0f);

			float moveSpeed = 0.0f;
			ML_SCRIPT_GETVALUE(moveSpeed, "HeroXJMoveSpeed");
			if(GetKeyState('A') & 0x8000)
			{
				vel.x -= moveSpeed;
				dir->SetDir(ML_DIR_LEFT);
			}
			else if(GetKeyState('D') & 0x8000)
			{
				vel.x += moveSpeed;
				dir->SetDir(ML_DIR_RIGHT);
			}

			pMovement->SetVel(vel.x, vel.y);

			static bool bPress = false;
			static float curFrame = 0.0f;
			float fireDelta = 0.0f;
			ML_SCRIPT_GETVALUE(fireDelta, "HeroXJFireDelta");
			if((GetKeyState('J') & 0x8000) && bPress == false)
			{
				MLStateMethod::Fire(entity);
				bPress = true;
			}

			if(bPress == true)
			{
				curFrame += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
				if(curFrame > fireDelta)
				{
					curFrame = 0.0f;
					bPress = false;
				}
			}
		}
	}
}

void MLXJNormalState::Move(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");
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
			VECTOR2 result;
			Vec2Add(result, pos, vel);
			pTransform->SetPos(result.x, result.y);
		}
	}
}