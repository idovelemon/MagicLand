#include "statemachine/ml_orgewalkstate.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"
#include "framerate/ml_frameratemgr.h"
#include "statemachine/ml_statemethod.h"
#include "support/script/ml_scriptmgr.h"

using namespace magicland;

MLOrgeWalkState::MLOrgeWalkState()
{
}

MLOrgeWalkState::~MLOrgeWalkState()
{
}

void MLOrgeWalkState::Enter(MLEntity* entity)
{
}

void MLOrgeWalkState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		Walk(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLOrgeWalkState::Exit(MLEntity* entity)
{
}

void MLOrgeWalkState::OnCollision(MLEntity* entity)
{
}

void MLOrgeWalkState::Walk(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component exist");

		MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
		ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exist");

		MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
		ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component exist");

		MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
		ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component exist");
		
		if(transform != NULL && timer != NULL && dir != NULL && userData != NULL)
		{
			VECTOR2 pos = transform->GetPos();

			// Walk period is up, choose random walk direction again
			float time = timer->GetTimer(ML_TIMER_FLAG_ORGE_WALK);
			float walkTime = 0.0f;
			ML_SCRIPT_GETVALUE(walkTime, "OrgeWalkTime");
			if(time > walkTime)
			{
				if(rand() % 2 == 0)
				{
					dir->SetDir(ML_DIR_LEFT);
				}
				else
				{
					dir->SetDir(ML_DIR_RIGHT);
				}

				timer->UpdateTimer(ML_TIMER_FLAG_ORGE_WALK, 0.0f);
			}
			else
			{
				time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
				timer->UpdateTimer(ML_TIMER_FLAG_ORGE_WALK, time);
			}

			// Check if walk out the range.If true, turn around.
			float centerX = *((float*)userData->GetValueByCategory(ML_USERDATA_FLAG_ORGE_CENTERX));
			float width = *((float*)userData->GetValueByCategory(ML_USERDATA_FLAG_ORGE_RANGE));
			if(abs(pos.x - centerX) > width/2.0f)
			{
				if(dir->GetDir() == ML_DIR_RIGHT)
				{
					dir->SetDir(ML_DIR_LEFT);
				}
				else
				{
					dir->SetDir(ML_DIR_RIGHT);
				}
			}

			// Walk
			float walkSpeed = 0.0f;
			ML_SCRIPT_GETVALUE(walkSpeed, "OrgeWalkSpeed");
			if(dir->GetDir() == ML_DIR_LEFT)
			{
				pos.x -= walkSpeed;
			}
			else
			{
				pos.x += walkSpeed;
			}

			transform->SetPos(pos.x, pos.y);
		}
	}
}