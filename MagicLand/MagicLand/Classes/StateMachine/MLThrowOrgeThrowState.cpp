#include "MLThrowOrgeThrowState.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "../Framerate/MLFrameRateMgr.h"
#include "../EntityComponent/MLEntityCreator.h"
#include "../EntityComponent/MLEntityMgr.h"
using namespace MagicLand;

MLThrowOrgeThrowState::MLThrowOrgeThrowState()
{
}

MLThrowOrgeThrowState::~MLThrowOrgeThrowState()
{
}

void MLThrowOrgeThrowState::Enter(MLEntity* entity)
{
}

void MLThrowOrgeThrowState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
	ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component is not empty");
	float time = timer->GetTimer(ML_TIMER_FLAG_THROWORGE_THROW);
	time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
	
	MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
	ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component is not empty");
	float deltaTime = *(float*)userData->GetValueByCategory(ML_USERDATA_FLAG_THROWORGE_THROWDELTA);
	if(time >= deltaTime)
	{
		// Throw a boom ball
		ThrowBoomBall(entity);

		time = 0.0f;
	}

	timer->UpdateTimer(ML_TIMER_FLAG_THROWORGE_THROW, time);
}

void MLThrowOrgeThrowState::Exit(MLEntity* entity)
{
}

void MLThrowOrgeThrowState::OnCollision(MLEntity* entity)
{
}

void MLThrowOrgeThrowState::ThrowBoomBall(MLEntity* entity)
{
	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 pos = transform->GetPos();

	MLEntity* boomBallEntity = MLEntityCreator::CreateBoomBall(pos.x, pos.y, entity->GetRoom());
	ML_SAFE_ASSERT(boomBallEntity != NULL, "Failed to create BoomBall");

	MLEntityMgr::SharedInstance()->AddEntity(boomBallEntity);
	ML_SAFE_DROP(boomBallEntity);
}