#include "MLStateMethod.h"
#include "../marco.h"
#include "../EntityComponent/MLEntityCreator.h"
#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComMovement.h"
#include "../EntityComponent/MLComDisplay.h"
#include "../EntityComponent/MLComDir.h"
#include "../EntityComponent/MLEntityMgr.h"

using namespace MagicLand;

void MLStateMethod::CollisionResponse(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not deal with null pointer");

	MLComTransform* transform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(transform != NULL, "There is no transform component");
	VECTOR2 pos = transform->GetPos();

	MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	MLComMovement* pMovement = (MLComMovement*)entity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	if(pBoundBox->IsCollided())
	{
		MLColVector& colEntities = pBoundBox->GetColEntities();

		for(int i = 0; i < colEntities.size(); i++)
		{
			MLEntity* pColEntity = colEntities[i];
			ML_SAFE_ASSERT(pColEntity != NULL, "There is an error");

			if(pColEntity->GetMainType() == ML_ETYMAINTYPE_ENV)
			{
				MLComBoundBox* pColBoundBox = (MLComBoundBox*)pColEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
				ML_SAFE_ASSERT(pColBoundBox != NULL, "There is no boundbox component");

				MLComTransform* pColTransform = (MLComTransform*)pColEntity->GetComponent(ML_COMTYPE_TRANSFORM);
				ML_SAFE_ASSERT(pColTransform != NULL, "There is no transform component");

				float colRatio = pColBoundBox->GetBoundBox().getHeight() / pColBoundBox->GetBoundBox().getWidth();

				VECTOR2 colPos = pColTransform->GetPos();
				VECTOR2 diff;
				Vec2Sub(diff, pos, colPos);
				float ratio = abs(diff.y) / abs(diff.x);

				if(ratio < colRatio) // Collided at x-axis
				{
					if(diff.x < 0) // Entity is at the left of the wall
					{
						pos.x = colPos.x - pColBoundBox->GetBoundBox().getWidth() / 2 - pBoundBox->GetBoundBox().getWidth()/2 - 0.1f;
					}
					else // Entity is at the right of the wall
					{
						pos.x = colPos.x + pColBoundBox->GetBoundBox().getWidth() / 2 + pBoundBox->GetBoundBox().getWidth()/2 + 0.1f;
					}
				}
				else // Collided at y-axis
				{
					if(diff.y < 0) // Entity is at the bottom of the wall
					{
						pos.y = colPos.y - pColBoundBox->GetBoundBox().getHeight()/2 - pBoundBox->GetBoundBox().getHeight()/2;
						
						// At the same time we should set the y-axis speed at 0
						VECTOR2 vel = pMovement->GetVel();
						vel.y = 0.0f;
						pMovement->SetVel(vel.x, vel.y);
					}
					else // Entity is at the top of the wall
					{
						pos.y = colPos.y + pColBoundBox->GetBoundBox().getHeight()/2 + pBoundBox->GetBoundBox().getHeight()/2;
					}
				}

				transform->SetPos(pos.x, pos.y);
			}
		}
	}
}

void MLStateMethod::UpdateBoundBox(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	pBoundBox->UpdateBoundBox(pTransform->GetPos());
}

void MLStateMethod::RenderSprite(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComDisplay* pDisplay = (MLComDisplay*)entity->GetComponent(ML_COMTYPE_DISPLAY);
	ML_SAFE_ASSERT(pDisplay != NULL, "There is no display component");

	VECTOR2 pos = pTransform->GetPos();
	pDisplay->GetSprite()->setPosition(ccp(pos.x, pos.y));

	float rot = pTransform->GetRot();
	pDisplay->GetSprite()->setRotation(rot);
}

void MLStateMethod::OnCollision(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLStateMethod::CollisionResponse(entity);

	MLStateMethod::UpdateBoundBox(entity);

	MLStateMethod::RenderSprite(entity);
}

void MLStateMethod::Fire(MLEntity* entity)
{
	ML_SAFE_ASSERT(entity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComDir* pDir = (MLComDir*)entity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(pDir != NULL, "There is no dir component");

	VECTOR2 pos = pTransform->GetPos();
	MLEntity* magic = MLEntityCreator::CreateFireBall(pos.x, pos.y, pDir->GetDir(), entity->GetRoom());
	MLEntityMgr::SharedInstance()->AddEntity(magic);
	ML_SAFE_DROP(magic);
}