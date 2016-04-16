#include "ml_orgewaitstate.h"

#include "../marco.h"
#include "../entitycomponent/ml_allcoms.h"
#include "../framerate/ml_frameratemgr.h"
#include "../support/script/ml_scriptmgr.h"

using namespace MagicLand;

MLOrgeWaitState::MLOrgeWaitState()
{
}

MLOrgeWaitState::~MLOrgeWaitState()
{
}

void MLOrgeWaitState::Enter(MLEntity* entity)
{
}

void MLOrgeWaitState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");
	if(entity != NULL)
	{
		MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
		ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exsit");
		if(timer != NULL)
		{
			float time = timer->GetTimer(ML_TIMER_FLAG_ORGE_WAIT);
			time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();

			float waitTime = 0.0f;
			ML_SCRIPT_GETVALUE(waitTime, "OrgeWaitTime");
			if(time >= waitTime)
			{
				time = 0.0f;
			}

			timer->UpdateTimer(ML_TIMER_FLAG_ORGE_WAIT, time);
		}
	}
}

void MLOrgeWaitState::Exit(MLEntity* entity)
{
}

void MLOrgeWaitState::OnCollision(MLEntity* entity)
{
}