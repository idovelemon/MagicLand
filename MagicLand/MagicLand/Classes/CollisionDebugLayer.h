//-----------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2015. All right reserved.
// Author: i_dovelemon(1322600812@qq.com)
// Date: 2016/01/02
// Version: 1.0
// Brief: This file will define the collision debug layer which will display
// all the entity's boundbox
//-----------------------------------------------------------------------
#ifndef __COLLISIONDEBUGLAYER__H_
#define __COLLISIONDEBUGLAYER__H_

#include <cocos2d.h>

class CollisionDebugLayer:public cocos2d::CCLayer
{
public:
	CollisionDebugLayer();
	virtual ~CollisionDebugLayer();

public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static node()" method manually
	CREATE_FUNC(CollisionDebugLayer);

	// implement the draw method
	void draw();

protected:
	void DrawPlayerBoundBox();
	void DrawPlayerMagicBoundBox();
	void DrawEnemeyBoundBox();
	void DrawEnvBoundBox();
	void DrawEnemyMagicBoundBox();
};

#endif