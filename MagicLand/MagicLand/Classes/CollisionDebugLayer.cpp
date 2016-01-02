#include "CollisionDebugLayer.h"
#include "Collision/MLCollisionMgr.h"
#include "marco.h"
#include "EntityComponent\MLComTransform.h"
#include "EntityComponent\MLComBoundBox.h"

using namespace MagicLand;

CollisionDebugLayer::CollisionDebugLayer()
{
}

CollisionDebugLayer::~CollisionDebugLayer()
{
}

// on "init" you need to initialize your instance
bool CollisionDebugLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        bRet = true;
    } while (0);

    return bRet;
}

void CollisionDebugLayer::draw()
{
	static bool bDraw = true;
	if(GetKeyState('C') & 0x8000)
	{
		bDraw = !bDraw;
	}

	if(bDraw)
	{
		DrawPlayerBoundBox();

		DrawEnvBoundBox();
	}
}

void CollisionDebugLayer::DrawPlayerBoundBox()
{
	ccDrawColor4B(0,255,0,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_PLAYER];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* pEntity = *it;
		ML_SAFE_ASSERT(pEntity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)pEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
		ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

		VECTOR2 pos = pTransform->GetPos();
		float width = pBoundBox->GetBoundBox().getWidth();
		float height = pBoundBox->GetBoundBox().getHeight();

		ccDrawLine(ccp(pos.x - width/2.0f, pos.y - height/2.0f),
			ccp(pos.x + width/2.0f, pos.y - height/2.0f));
		ccDrawLine(ccp(pos.x + width/2.0f, pos.y - height/2.0f),
			ccp(pos.x + width/2.0f, pos.y + height/2.0f));
		ccDrawLine(ccp(pos.x + width/2.0f, pos.y + height/2.0f),
			ccp(pos.x - width/2.0f, pos.y + height/2.0f));
		ccDrawLine(ccp(pos.x - width/2.0f, pos.y + height/2.0f),
			ccp(pos.x - width/2.0f, pos.y - height/2.0f));
	}
}

void CollisionDebugLayer::DrawEnvBoundBox()
{
	ccDrawColor4B(255,0,0,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_ENV];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* pEntity = *it;
		ML_SAFE_ASSERT(pEntity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)pEntity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)pEntity->GetComponent(ML_COMTYPE_BOUNDBOX);
		ML_SAFE_ASSERT(pBoundBox != NULL, "There is no boundbox component");

		VECTOR2 pos = pTransform->GetPos();
		float width = pBoundBox->GetBoundBox().getWidth();
		float height = pBoundBox->GetBoundBox().getHeight();

		ccDrawLine(ccp(pos.x - width/2.0f, pos.y - height/2.0f),
			ccp(pos.x + width/2.0f, pos.y - height/2.0f));
		ccDrawLine(ccp(pos.x + width/2.0f, pos.y - height/2.0f),
			ccp(pos.x + width/2.0f, pos.y + height/2.0f));
		ccDrawLine(ccp(pos.x + width/2.0f, pos.y + height/2.0f),
			ccp(pos.x - width/2.0f, pos.y + height/2.0f));
		ccDrawLine(ccp(pos.x - width/2.0f, pos.y + height/2.0f),
			ccp(pos.x - width/2.0f, pos.y - height/2.0f));
	}
}