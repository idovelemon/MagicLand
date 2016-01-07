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

void MLStateMethod::CollisionResponse(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");
	VECTOR2 pos = pTransform->GetPos();

	MLComBoundBox* pBoundBox = (MLComBoundBox*)pEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
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

				MLComTransform* pTransform = (MLComTransform*)pColEntity->GetComponent(ML_COMTYPE_TRANSFORM);
				ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

				float colRatio = pColBoundBox->GetBoundBox().getHeight() / pColBoundBox->GetBoundBox().getWidth();

				VECTOR2 colPos = pTransform->GetPos();
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
			}
		}

		pTransform->SetPos(pos.x, pos.y);
	}
}

void MLStateMethod::UpdateBoundBox(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLComBoundBox* pBoundBox = (MLComBoundBox*)pEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	pBoundBox->UpdateBoundBox(pTransform->GetPos());
}

void MLStateMethod::RenderSprite(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComDisplay* pDisplay = (MLComDisplay*)pEntity->GetComponent(ML_COMTYPE_DISPLAY);
	ML_SAFE_ASSERT(pDisplay != NULL, "There is no display component");

	VECTOR2 pos = pTransform->GetPos();
	pDisplay->GetSprite()->setPosition(ccp(pos.x, pos.y));
}

void MLStateMethod::OnCollision(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLStateMethod::CollisionResponse(pEntity);

	MLStateMethod::UpdateBoundBox(pEntity);

	MLStateMethod::RenderSprite(pEntity);
}

void MLStateMethod::Fire(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not pass the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

	MLComDir* pDir = (MLComDir*)pEntity->GetComponent(ML_COMTYPE_DIR);
	ML_SAFE_ASSERT(pDir != NULL, "There is no dir component");

	VECTOR2 pos = pTransform->GetPos();
	MLEntity* magic = MLEntityCreator::CreateFireBall(pos.x, pos.y, pDir->GetDir(), pEntity->GetRoom());
	MLEntityMgr::SharedInstance()->AddEntity(magic);
}