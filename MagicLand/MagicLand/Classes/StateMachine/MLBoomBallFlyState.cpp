#include "MLBoomBallFlyState.h"

#include "../marco.h"
#include "MLStateMethod.h"
#include "../EntityComponent/MLAllComs.h"
#include "../EntityComponent/MLEntityCreator.h"
#include "../EntityComponent/MLEntityMgr.h"
#include "../Support/Script/MLScriptMgr.h"

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
	if(entity != NULL)
	{
		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
		if(movement != NULL)
		{
			movement->SetVel(MLScriptMgr::SharedInstance()->GetValue("BoomBallFlyVelX"), MLScriptMgr::SharedInstance()->GetValue("BoomBallFlyVelY"));
		}
	}
}

void MLBoomBallFlyState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		Fly(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLBoomBallFlyState::Exit(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		Boom(entity);
	}
}

void MLBoomBallFlyState::OnCollision(MLEntity* entity)
{
	MLStateMethod::OnCollision(entity);
}

void MLBoomBallFlyState::Fly(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
		if(transform != NULL)
		{
			VECTOR2 pos = transform->GetPos();
			float rot = transform->GetRot();

			MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
			ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
			if(movement != NULL)
			{
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
		}
	}
}

void MLBoomBallFlyState::Boom(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		float maxVelX = 0.0f, minVelX = 0.0f, maxVelY = 0.0f, minVelY = 0.0f;
		int maxBoomNum = 0, minBoomNum = 0;

		ML_SCRIPT_GETVALUE(maxVelX, "BrokenStoneVelXMax");
		ML_SCRIPT_GETVALUE(minVelX, "BrokenStoneVelXMin");
		ML_SCRIPT_GETVALUE(maxVelY, "BrokenStoneVelYMax");
		ML_SCRIPT_GETVALUE(minVelY, "BrokenStoneVelYMin");
		ML_SAFE_ASSERT(maxVelY > 0, "Make sure the BrokeStoneVelYMax is bigger than 0");
		ML_SAFE_ASSERT(minVelY > 0, "Make sure the BrokeStoneVelYMin is bigger than 0");

		ML_SCRIPT_GETVALUE(maxBoomNum, "BoomBallMaxBrokenStoneNum");
		ML_SCRIPT_GETVALUE(minBoomNum, "BoomBallMinBrokenStoneNum");
		ML_SAFE_ASSERT(maxBoomNum > 0, "Make sure the Max Boom Num is bigger than 0");
		ML_SAFE_ASSERT(minBoomNum > 0, "Make sure the Min Boom Num is bigger than 0");

		if(maxVelY > 0 && minVelY > 0 && maxBoomNum > 0 && minBoomNum > 0)
		{
			MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
			ML_SAFE_ASSERT(transform != NULL, "Make sure the Transform component is not empty");
			if(transform != NULL)
			{
				VECTOR2 pos = transform->GetPos();

				srand(time(NULL));
				int boomNum = minBoomNum + rand() % (maxBoomNum - minBoomNum);
				int dir = 0;
				if(rand() % 2 == 0)
				{
					dir = 1;
				}
				else
				{
					dir = -1;
				}

				for(int i = 0; i < boomNum; i++)
				{
					float velx = minVelX + rand() % (int)(maxVelX - minVelX);
					float vely = minVelY + rand() % (int)(maxVelY - minVelY);

					velx = dir * velx;
					dir = -dir;

					MLEntity* brokenStone = MLEntityCreator::CreateBrokenStone(pos.x, pos.y,velx, vely, entity->GetRoom());
					MLEntityMgr::SharedInstance()->AddEntity(brokenStone);
					ML_SAFE_DROP(brokenStone);
				}
			}
		}
	}
}