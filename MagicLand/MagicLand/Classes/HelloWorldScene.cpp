#include "HelloWorldScene.h"
#include "Round\MLRoomCreator.h"
#include "StateMachine\MLStateMachineMgr.h"
#include "Collision\MLCollisionMgr.h"
#include "EntityComponent\MLEntityMgr.h"
#include "StateMachine\MLComCon.h"
#include "StateMachine\MLStartState.h"
#include "StateMachine\MLXJNormalState.h"
#include "StateMachine\MLXJJumpState.h"
#include "StateMachine\MLXJFallState.h"
#include "marco.h"

using namespace cocos2d;
using namespace MagicLand;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
		scene->addChild(layer->getDebugLayer(), 100);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
		scheduleUpdate();

		m_DebugLayer = CollisionDebugLayer::create();
		CCPoint pos = getPosition();
		m_DebugLayer->setPosition(ccp(pos.x, pos.y));
		bRet = true;

    } while (0);

    return bRet;
}

CCLayer* HelloWorld::getDebugLayer()
{
	return m_DebugLayer;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

void HelloWorld::update(float delta)
{
	static bool hasCreated = false;
	if(!hasCreated)
	{
		// Create room here...
		MLRoomCreator* creator = new MLRoomCreator("test.rmd");
		ML_SAFE_ASSERT(creator != NULL, "Failed to allocate memory for the creator");
		m_Room = creator->CreateRoom();
		ML_SAFE_DROP(creator);

		// Create State machine here...
		MLStateMachine* pHeroXJSM = new MLStateMachine;
		ML_SAFE_ASSERT(pHeroXJSM != NULL, "Failed to allocate the memory for the state machine");

		// Create the state
		MLXJNormalState* normalState = new MLXJNormalState();
		ML_SAFE_ASSERT(normalState != NULL, "Failed to allocate the memory for the normal state");

		MLXJJumpState* jumpState = new MLXJJumpState();
		ML_SAFE_ASSERT(jumpState != NULL, "Failed to allocate the memory for the jump state");

		MLXJFallState* fallState = new MLXJFallState();
		ML_SAFE_ASSERT(fallState != NULL, "Failed to allocate the memory for fall state");

		// Build the state transform table
		pHeroXJSM->AddStateEntry(MLStartState::SharedInstance(), &MLComCon::StartOK, fallState);
		pHeroXJSM->AddStateEntry(fallState, &MLComCon::TouchGround, normalState);
		pHeroXJSM->AddStateEntry(normalState, &MLComCon::NeedJump, jumpState);
		pHeroXJSM->AddStateEntry(jumpState, &MLComCon::TouchGround, normalState);
		pHeroXJSM->AddStateEntry(normalState, &MLComCon::NeedFall, fallState);

		MLStateMachineMgr::SharedInstance()->AddMgrEntry(ML_ETYSUBTYPE_XJ, pHeroXJSM);

		// Create Collision manager here...
		MLCollisionMgr::SharedInstance();

		hasCreated = true;
	}
	else
	{
		// Update the collision system
		MLCollisionMgr::SharedInstance()->Update(delta);

		// Update the entity system
		MLEntityMgr::SharedInstance()->Update(delta);
	}
}