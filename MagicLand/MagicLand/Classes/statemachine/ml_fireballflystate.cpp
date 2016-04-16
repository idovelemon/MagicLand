#include "statemachine/ml_fireballflystate.h"

#include "marco.h"
#include "entitycomponent/ml_allcoms.h"
#include "entitycomponent/ml_timerflag.h"
#include "framerate/ml_frameratemgr.h"
#include "statemachine/ml_statemethod.h"

using namespace magicland;

MLFireBallFlyState::MLFireBallFlyState()
{
}

MLFireBallFlyState::~MLFireBallFlyState()
{
}

void MLFireBallFlyState::Enter(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");
	if(entity != NULL)
	{
		MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
		ML_SAFE_ASSERT(timer != NULL, "There is no timer component");
		if(timer != NULL)
		{
			timer->AddTimer(ML_TIMER_FLAG_FIREBALL_FLY);
		}
	}
}

void MLFireBallFlyState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");
	if(entity != NULL)
	{
		Fly(entity);

		UpdateFlyTimer(entity);

		MLStateMethod::UpdateBoundBox(entity);

		MLStateMethod::RenderSprite(entity);
	}
}

void MLFireBallFlyState::Exit(MLEntity* entity)
{
}

void MLFireBallFlyState::OnCollision(MLEntity* entity)
{
}

void MLFireBallFlyState::Fly(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with empty entity");
	if(entity != NULL)
	{
		MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(transform != NULL, "There is no transform component");

		MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
		ML_SAFE_ASSERT(movement != NULL, "There is no movement component");

		if(transform != NULL && movement != NULL)
		{
			VECTOR2 pos = transform->GetPos();
			VECTOR2 vel = movement->GetVel();
			Vec2Add(pos, pos, vel);
			transform->SetPos(pos.x, pos.y);
		}
	}
}

void MLFireBallFlyState::UpdateFlyTimer(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with empty entity");
	if(entity != NULL)
	{
		MLComTimer* timer = (MLComTimer*)entity->GetComponent(ML_COMTYPE_TIMER);
		ML_SAFE_ASSERT(timer != NULL, "There is no timer component");
		if(timer != NULL)
		{
			float time = timer->GetTimer(ML_TIMER_FLAG_FIREBALL_FLY);
			time += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
			timer->UpdateTimer(ML_TIMER_FLAG_FIREBALL_FLY, time);
		}
	}
}