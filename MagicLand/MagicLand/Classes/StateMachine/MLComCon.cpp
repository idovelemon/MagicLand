#include "MLComCon.h"
#include "../marco.h"
#include "../EntityComponent/MLComTransform.h"
#include "../EntityComponent/MLComBoundBox.h"
#include "../EntityComponent/MLComMovement.h"
using namespace MagicLand;

bool MLComCon::StartOK(MLEntity* pEntity)
{
	return true;
}

bool MLComCon::NeedJump(MLEntity* pEntity)
{
	if(GetKeyState('W') & 0x8000)
	{
		return true;
	}

	return false;
}

bool MLComCon::TouchGround(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with the null pointer");

	MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
	ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");
	VECTOR2 pos = pTransform->GetPos();

	MLComBoundBox* pBoundBox = (MLComBoundBox*)pEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
	ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

	bool bRet = false;
	if(pBoundBox->IsCollided())
	{
		MLColVector& colEntities = pBoundBox->GetColEntities();

		for(int i = 0; i < colEntities.size(); i++)
		{
			MLEntity* pColEntity = colEntities[i];
			ML_SAFE_ASSERT(pColEntity != NULL, "There is an empty entity");

			MLComTransform* pColTransform = (MLComTransform*)pColEntity->GetComponent(ML_COMTYPE_TRANSFORM);
			ML_SAFE_ASSERT(pColTransform != NULL, "There is no transform component");

			MLComBoundBox* pColBoundBox = (MLComBoundBox*)pColEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
			ML_SAFE_ASSERT(pColBoundBox != NULL, "There is no boundbox component");

			float colRatio = pColBoundBox->GetBoundBox().getHeight() / pColBoundBox->GetBoundBox().getWidth();

			VECTOR2 colPos = pColTransform->GetPos();
			VECTOR2 diff;
			Vec2Sub(diff, pos, colPos);
			float ratio = abs(diff.y) / abs(diff.x);

			if(ratio >= colRatio) // Collided in y-axis
			{
				if(diff.y > 0) // Entity is at the top of the collided entity
				{
					// So touch the ground
					bRet = true;
					break;
				}
			}
		}
	}

	return bRet;
}

bool MLComCon::NeedFall(MLEntity* pEntity)
{
	ML_SAFE_ASSERT(pEntity != NULL, "Can not deal with null pointer");

	MLComMovement* pMovement = (MLComMovement*)pEntity->GetComponent(ML_COMTYPE_MOVEMENT);
	ML_SAFE_ASSERT(pMovement != NULL, "There is no movement component");

	bool bRet = false;

	if(pMovement->GetVel().y <= 0.0f)
	{
		if(!TouchGround(pEntity))
		{
			bRet = true;
		}
	}

	return bRet;
}