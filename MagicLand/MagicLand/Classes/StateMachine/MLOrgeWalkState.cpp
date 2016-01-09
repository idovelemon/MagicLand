#include "MLOrgeWalkState.h"
#include "../EntityComponent/MLAllComs.h"
#include "../marco.h"
#include "../EntityComponent/MLComOrgeWalkRange.h"
#include "../Framerate/MLFrameRateMgr.h"
#include "MLStateMethod.h"
using namespace MagicLand;

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

	Walk(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
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

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component exist");
	VECTOR2 pos = transform->GetPos();

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exist");

	MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component exist");

	MLComOrgeWalkRange* orgeWalkRange = (MLComOrgeWalkRange*)entity->GetComponent(ML_COMTYPE_ORGE_WALKRANGE);
	ML_SAFE_ASSERT(orgeWalkRange != NULL, "Please make sure the OrgeWalkRange component exist");

	// Walk period is up, choose random walk direction again
	float walkTime = timer->GetTimer(ML_TIMER_FLAG_ORGE_WALK);
	if(walkTime > 2.0f)
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
		walkTime += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
		timer->UpdateTimer(ML_TIMER_FLAG_ORGE_WALK, walkTime);
	}

	// Check if walk out the range.If true, turn around.
	if(abs(pos.x - orgeWalkRange->GetCenterX()) > orgeWalkRange->GetWidth()/2.0f)
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
	if(dir->GetDir() == ML_DIR_LEFT)
	{
		pos.x -= 1.0f;
	}
	else
	{
		pos.x += 1.0f;
	}

	transform->SetPos(pos.x, pos.y);
}