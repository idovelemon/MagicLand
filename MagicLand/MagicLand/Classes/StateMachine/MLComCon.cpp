#include "MLComCon.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "../EntityComponent/MLTimerFlag.h"
#include "../EntityComponent/MLEntityMgr.h"
#include "../Support/Script/MLScriptMgr.h"
using namespace MagicLand;

bool MLComCon::StartOK(MLEntity* entity)
{
	return true;
}

bool MLComCon::NeedEnd(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	
	MLComState* state = (MLComState*)entity->GetComponent(ML_COMTYPE_STATE);
	ML_SAFE_ASSERT(state != NULL, "Please make sure the State component exist");

	return state->IsNeedEnd();
}

bool MLComCon::NeedJump(MLEntity* entity)
{
	if(GetKeyState('W') & 0x8000)
	{
		return true;
	}

	return false;
}

bool MLComCon::TouchGround(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with the null pointer");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");
	VECTOR2 pos = pTransform->GetPos();

	MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	bool bRet = false;
	if(pBoundBox->IsCollided())
	{
		MLColVector& colEntities = pBoundBox->GetColEntities();

		for(int i = 0; i < colEntities.size(); i++)
		{
			MLEntity* pColEntity = colEntities[i];
			ML_SAFE_ASSERT(pColEntity != NULL, "There is an empty entity");

			MLComTransform* pColTransform = (MLComTransform*)pColEntity->GetComponent(ML_COMTYPE_TRANSFORM);
			ML_SAFE_ASSERT(pColTransform != NULL, "There is no transform component");

			MLComBoundBox* pColBoundBox = (MLComBoundBox*)pColEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(pColBoundBox != NULL, "There is no boundbox component");

			if(pColEntity->GetMainType() == ML_ETYMAINTYPE_ENV)
			{
				float colRatio = pColBoundBox->GetBoundBox().getHeight() / pColBoundBox->GetBoundBox().getWidth();

				VECTOR2 colPos = pColTransform->GetPos();
				VECTOR2 diff;
				Vec2Sub(diff, pos, colPos);
				float ratio = abs(diff.y) / abs(diff.x);

				if(ratio >= colRatio) // Collided in y-axis
				{
					if(diff.y > 0) // Entity is at the top of the collided entity
					{
						// So touch the ground
						bRet = true;
						break;
					}
				}
			}
		}
	}

	return bRet;
}

bool MLComCon::NeedFall(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");

	MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	bool bRet = false;

	if(pMovement->GetVel().y <= 0.0f)
	{
		if(!TouchGround(entity))
		{
			bRet = true;
		}
	}

	return bRet;
}

bool MLComCon::FireBallFlyTimeUp(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with empty entity");

	bool bRet = false;

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "There is no timer component");

	float time = timer->GetTimer(ML_TIMER_FLAG_FIREBALL_FLY);
	if(time > 2.0f)
	{
		bRet = true;
	}

	return bRet;
}

bool MLComCon::FireBallCollidedWithEnemy(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	bool bRet = false;

	MLComBoundBox* boundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(boundBox != NULL, "Please make sure the BoundBox component exsit");

	if(boundBox->IsCollided())
	{
		MLColVector& colVec = boundBox->GetColEntities();
		for(int i = 0; i < colVec.size(); i++)
		{
			if(colVec[i]->GetMainType() == ML_ETYMAINTYPE_ENEMY)
			{
				bRet = true;
				break;
			}
		}
	}

	return bRet;
}

bool MLComCon::OrgeWaitTimeUp(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	bool bRet = false;

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exist");

	float time = timer->GetTimer(ML_TIMER_FLAG_ORGE_WAIT);
	if(ML_FLOAT_EQUAL(time, 0.0f))
	{
		bRet = true;
	}

	return bRet;
}

bool MLComCon::OrgeWalkTimeUp(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	bool bRet = false;

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exist");

	float time = timer->GetTimer(ML_TIMER_FLAG_ORGE_WALK);
	if(ML_FLOAT_EQUAL(time, 0.0f))
	{
		bRet = true;
	}

	return bRet;
}

bool MLComCon::JumpOrgeSeePlayer(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	bool bRet = false;
	MLEntity* player = MLEntityMgr::SharedInstance()->GetPlayer();
	ML_SAFE_ASSERT(player != NULL, "Please make sure the player is not empty");

	MLComTransform* playerTransform = (MLComTransform*)player->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(playerTransform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 playerPos = playerTransform->GetPos();

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 pos = transform->GetPos();

	float realLength = 0.0f;
	Vec2Sub(pos, pos, playerPos);
	Vec2Length(realLength, pos);

	float distance = 0.0f;
	ML_SCRIPT_GETVALUE(distance, "JumpOrgeWatchDistance");

	if(realLength < distance)
	{
		bRet = true;
	}

	return bRet;
}

bool MLComCon::JumpOrgeIsBack(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	bool bRet = false;

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");

	MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
	ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component is not empty");
	VECTOR2* pInitPos = (VECTOR2*)userData->GetValueByCategory(ML_USERDATA_FLAG_JUMPORGE_INITPOS);

	MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component is not empty");

	if(dir->GetDir() == ML_DIR_LEFT)
	{
		if(transform->GetPos().x < pInitPos->x)
		{
			bRet = true;
		}
	}
	else if(dir->GetDir() == ML_DIR_RIGHT)
	{
		if(transform->GetPos().x > pInitPos->x)
		{
			bRet = true;
		}
	}

	return bRet;
}