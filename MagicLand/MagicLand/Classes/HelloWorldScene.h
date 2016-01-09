#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CollisionDebugLayer.h"
#include "Round/MLRoom.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float delta);

	cocos2d::CCLayer* getDebugLayer();

protected:
    MagicLand::MLRoom* m_Room;
	CollisionDebugLayer* m_DebugLayer;
	cocos2d::CCLabelTTF* m_CollisionNo;
	cocos2d::CCLabelTTF* m_EntityNo;
};

#endif  // __HELLOWORLD_SCENE_H__