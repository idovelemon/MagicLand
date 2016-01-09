#include "MLOrgeWaitState.h"
#include "../EntityComponent/MLAllComs.h"
#include "../marco.h"
#include "../Framerate/MLFrameRateMgr.h"
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

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component exsit");

	float time = timer->GetTimer(ML_TIMER_FLAG_ORGE_WAIT);
	time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();

	if(time >= 1.0f)
	{
		time = 0.0f;
	}

	timer->UpdateTimer(ML_TIMER_FLAG_ORGE_WAIT, time);
}

void MLOrgeWaitState::Exit(MLEntity* entity)
{
}

void MLOrgeWaitState::OnCollision(MLEntity* entity)
{
}