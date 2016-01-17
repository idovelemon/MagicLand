#include "MLMovePlatformMoveState.h"
#include "../marco.h"
#include "../EntityComponent/MLAllComs.h"
#include "MLStateMethod.h"
using namespace MagicLand;

MLMovePlatformMoveState::MLMovePlatformMoveState()
{
}

MLMovePlatformMoveState::~MLMovePlatformMoveState()
{
}

void MLMovePlatformMoveState::Enter(MLEntity* entity)
{
}

void MLMovePlatformMoveState::Run(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	Move(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLMovePlatformMoveState::Exit(MLEntity* entity)
{
}

void MLMovePlatformMoveState::OnCollision(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComBoundBox* boundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(boundBox != NULL, "Please make sure the BoundBox is not empty");

	MLColVector colEntities = boundBox->GetColEntities();
	for(int i = 0; i < colEntities.size(); i++)
	{
		MLEntity* player = colEntities[i];
		ML_SAFE_ASSERT(player != NULL, "Please make sure the entity is not empty");
		if(player->GetMainType() == ML_ETYMAINTYPE_PLAYER)
		{
			MLComTransform* playerTransform = (MLComTransform*)player->GetComponent(ML_COMTYPE_TRANSFORM);
			ML_SAFE_ASSERT(playerTransform != NULL, "Please make sure the Transform component is not empty");
			VECTOR2 pos = playerTransform->GetPos();

			MLComUserData* entityUserData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
			ML_SAFE_ASSERT(entityUserData != NULL, "Please make sure the UserData component is not empty");
			float diff = *(float*)entityUserData->GetValueByCategory(ML_USERDATA_FLAG_MOVEPLATFORM_DIFF);
			pos.x += diff;

			playerTransform->SetPos(pos.x, pos.y);
			break;
		}
	}
}

void MLMovePlatformMoveState::Move(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Please make sure the entity is not empty");

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "Please make sure the Transform component is not empty");
	VECTOR2 pos = transform->GetPos();
	VECTOR2 lastFramePos = pos;

	MLComMovement* movement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(movement != NULL, "Please make sure the Movement component is not empty");
	VECTOR2 vel = movement->GetVel();

	MLComDir* dir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(dir != NULL, "Please make sure the Dir component is not empty");
	MLDir ori = dir->GetDir();

	MLComUserData* userData = (MLComUserData*)entity->GetComponent(ML_COMTYPE_USERDATA);
	ML_SAFE_ASSERT(userData != NULL, "Please make sure the UserData component is not empty");
	float initPos = *(float*)userData->GetValueByCategory(ML_USERDATA_FLAG_MOVEPLATFORM_INITPOS);
	float width = *(float*)userData->GetValueByCategory(ML_USERDATA_FLAG_MOVEPLATFORM_WIDTH);
	float *pDiff = (float*)userData->GetValueByCategory(ML_USERDATA_FLAG_MOVEPLATFORM_DIFF);

	Vec2Add(pos, pos, vel);
	if(pos.x < initPos && ori == ML_DIR_LEFT)
	{
		pos.x = initPos;
		vel.x = -vel.x;
		ori = ML_DIR_RIGHT;
	}
	else if(pos.x > initPos + width && ori == ML_DIR_RIGHT)
	{
		pos.x = initPos + width;
		vel.x = -vel.x;
		ori = ML_DIR_LEFT;
	}

	transform->SetPos(pos.x, pos.y);
	movement->SetVel(vel.x, vel.y);
	dir->SetDir(ori);
	*pDiff = (pos.x - lastFramePos.x);
}