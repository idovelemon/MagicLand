#include "HelloWorldScene.h"
#include "Round\MLRound.h"

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
	m_DebugLayer->setPosition(MLRound::SharedInstance()->GetCurRoom()->GetGameLayer()->getPosition());
}