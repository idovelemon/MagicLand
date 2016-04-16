#include "statemachine/ml_throworgethrowstate.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"
#include "entitycomponent/ml_entitycreator.h"
#include "entitycomponent/ml_entitymgr.h"
#include "framerate/ml_frameratemgr.h"

using namespace magicland;

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
	if(entity != NULL)
	{
		MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
		ML_SAFE_ASSERT(timer != NULL, "Please make sure the Timer component is not empty");
	
		MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
		ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component is not empty");

		if(timer != NULL && userData != NULL)
		{
			float time = timer->GetTimer(ML_TIMER_FLAG_THROWORGE_THROW);
			time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();

			float deltaTime = *(float*)userData->GetValueByCategory(ML_USERDATA_FLAG_THROWORGE_THROWDELTA);
			if(time >= deltaTime)
			{
				// Throw a boom ball
				ThrowBoomBall(entity);

				time = 0.0f;
			}

			timer->UpdateTimer(ML_TIMER_FLAG_THROWORGE_THROW, time);
		}
	}
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
	if(transform != NULL)
	{
		VECTOR2 pos = transform->GetPos();

		MLEntity* boomBallEntity = MLEntityCreator::CreateBoomBall(pos.x, pos.y, entity->GetRoom());
		ML_SAFE_ASSERT(boomBallEntity != NULL, "Failed to create BoomBall");
		if(boomBallEntity != NULL)
		{
			MLEntityMgr::SharedInstance()->AddEntity(boomBallEntity);
			ML_SAFE_DROP(boomBallEntity);
		}
	}
}