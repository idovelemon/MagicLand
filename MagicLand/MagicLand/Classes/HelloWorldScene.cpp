#include "HelloWorldScene.h"
#include "Round\MLRound.h"
#include "Collision\MLCollisionMgr.h"
#include "EntityComponent\MLEntityMgr.h"

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
        scene->addChild(layer, 100);
		scene->addChild(layer->getDebugLayer(), 99);
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

		
		m_CollisionNo = CCLabelTTF::create("Collision Volume Number:","Consolas", 24);
		m_CollisionNo->setPosition(ccp(0, 590));
		m_CollisionNo->setAnchorPoint(ccp(0.0f, 0.5f));
		addChild(m_CollisionNo);

		m_EntityNo = CCLabelTTF::create("Entity Number:","Consolas", 24);
		m_EntityNo->setPosition(ccp(0, 570));
		m_EntityNo->setAnchorPoint(ccp(0.0f, 0.5f));
		addChild(m_EntityNo);

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
	m_DebugLayer->setPosition(MLRound::SharedInstance()->GetCurRoom()->GetGameLayer()->getPosition());

	MLCollisionMgr*colMgr = MLCollisionMgr::SharedInstance();
	if(colMgr != NULL)
	{
		char temp[32];
		sprintf(temp, "Collision Volume Number: %d", colMgr->GetCVNum());
		m_CollisionNo->setString(temp);
	}

	MLEntityMgr* entityMgr = MLEntityMgr::SharedInstance();
	if(entityMgr != NULL)
	{
		char temp[32];
		sprintf(temp, "Entity Number: %d", entityMgr->GetEntityNum());
		m_EntityNo->setString(temp);
	}
}