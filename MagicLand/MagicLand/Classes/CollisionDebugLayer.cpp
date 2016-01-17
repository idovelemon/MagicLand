#include "CollisionDebugLayer.h"
#include "Collision/MLCollisionMgr.h"
#include "marco.h"
#include "EntityComponent\MLComTransform.h"
#include "EntityComponent\MLComBoundBox.h"
#include "Framerate\MLFrameRateMgr.h"

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
	static bool bDraw = false;
	static bool bPress = false;
	static float curFrame = 0.0f;
	if((GetAsyncKeyState('C') & 0x8000) && (bPress == false))
	{
		bDraw = !bDraw;
		bPress = true;
	}

	if(bPress == true)
	{
		curFrame += MLFrameRateMgr::SharedInstance()->GetFrameDelta();
		if(curFrame > 0.2f)
		{
			curFrame = 0.0f;
			bPress = false;
		}
	}

	if(bDraw)
	{
		DrawPlayerBoundBox();

		DrawPlayerMagicBoundBox();

		DrawEnemeyBoundBox();

		DrawEnvBoundBox();

		DrawEnemyMagicBoundBox();
	}
}

void CollisionDebugLayer::DrawPlayerBoundBox()
{
	ccDrawColor4B(0,255,0,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_PLAYER];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* entity = *it;
		ML_SAFE_ASSERT(entity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
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

void CollisionDebugLayer::DrawPlayerMagicBoundBox()
{
	ccDrawColor4B(255,255,0,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_PLAYER_MAGIC];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* entity = *it;
		ML_SAFE_ASSERT(entity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
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
		MLEntity* entity = *it;
		ML_SAFE_ASSERT(entity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
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

void CollisionDebugLayer::DrawEnemeyBoundBox()
{
	ccDrawColor4B(0,0,255,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_ENEMY];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* entity = *it;
		ML_SAFE_ASSERT(entity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
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

void CollisionDebugLayer::DrawEnemyMagicBoundBox()
{
	ccDrawColor4B(0,255,255,255);
	std::vector<std::list<MLEntity*>> colTable = MLCollisionMgr::SharedInstance()->GetColTable();

	std::list<MLEntity*> entityList = colTable[ML_ETYMAINTYPE_ENEMYMAGIC];
	for(std::list<MLEntity*>::iterator it = entityList.begin(); it != entityList.end(); ++it)
	{
		MLEntity* entity = *it;
		ML_SAFE_ASSERT(entity != NULL, "There is an error");

		MLComTransform* pTransform = (MLComTransform*)entity->GetComponent(ML_COMTYPE_TRANSFORM);
		ML_SAFE_ASSERT(pTransform != NULL, "There is no transform component");

		MLComBoundBox* pBoundBox = (MLComBoundBox*)entity->GetComponent(ML_COMTYPE_BOUNDBOX);
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