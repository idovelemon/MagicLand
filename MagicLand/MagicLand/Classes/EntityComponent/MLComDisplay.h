//------------------------------------------------------------------------
// Declaration: Copyright (c), by xiaojian, 2015. All right reserved.
// Author: xiaojian
// Date: 2015/12/06
// Version: 1.0
// Breif: This file will define the display component, which deal with
// the communicate with the cocos2d.All the display element will handle
// in this component
//------------------------------------------------------------------------
#ifndef ML_ENTITYCOMONENT_MLCOMDISPLAY_H_
#define ML_ENTITYCOMONENT_MLCOMDISPLAY_H_

#include <cocos2d.h>

#include "MLComponent.h"

namespace MagicLand 
{ 
	class MLComDisplay;
};

class MagicLand::MLComDisplay:public MLComponent
{
public:
	MLComDisplay(MagicLand::MLEntity* entity, char* fileName, cocos2d::CCLayer* parentLayer);
    virtual ~MLComDisplay();

public:
	virtual cocos2d::CCSprite* GetSprite() const;

public:
	cocos2d::CCLayer*	m_Layer;	// This layer will hold all the display element in this component
	cocos2d::CCSprite*	m_Sprite;	// This sprite will display the image of the entity
};

#endif // ML_ENTITYCOMONENT_MLCOMDISPLAY_H_