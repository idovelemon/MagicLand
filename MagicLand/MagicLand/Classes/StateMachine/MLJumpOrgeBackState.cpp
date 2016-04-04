#include "MLJumpOrgeBackState.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "../Support/Script/MLScriptMgr.h"
#include "MLStateMethod.h"
using namespace MagicLand;

MLJumpOrgeBackState::MLJumpOrgeBackState()
{
}

MLJumpOrgeBackState::~MLJumpOrgeBackState()
{
}

void MLJumpOrgeBackState::Enter(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");

		MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
		ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component is not empty");

		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");

		MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
		ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component is not empty");

		if(movement != NULL && userData != NULL && transform != NULL && dir != NULL)
		{
			VECTOR2 *initPos = (VECTOR2*)userData->GetValueByCategory(ML_USERDATA_FLAG_JUMPORGE_INITPOS);
			VECTOR2 pos = transform->GetPos();

			float moveSpeed = 0.0f;
			ML_SCRIPT_GETVALUE(moveSpeed, "JumpOrgeMoveSpeed");
			if(initPos->x < pos.x) // The JumpOrge jump to the right, so move left
			{
				movement->SetVel(-moveSpeed, 0.0f);
				dir->SetDir(ML_DIR_LEFT);
			}
			else
			{
				movement->SetVel(moveSpeed, 0.0f);
				dir->SetDir(ML_DIR_RIGHT);
			}
		}
	}
}

void MLJumpOrgeBackState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		Back(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLJumpOrgeBackState::Exit(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
		movement->SetVel(0.0f, 0.0f);
	}
}

void MLJumpOrgeBackState::OnCollision(MLEntity* entity)
{
}

void MLJumpOrgeBackState::Back(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");

		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");

		if(transform != NULL && movement != NULL)
		{
			VECTOR2 pos = transform->GetPos();
			VECTOR2 vel = movement->GetVel();

			Vec2Add(pos, pos, vel);
	
			transform->SetPos(pos.x, pos.y);
		}
	}
}