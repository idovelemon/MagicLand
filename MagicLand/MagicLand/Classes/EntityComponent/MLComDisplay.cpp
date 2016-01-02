#include "MLComDisplay.h"
#include "../marco.h"
using namespace MagicLand;
using namespace cocos2d;

MLComDisplay::MLComDisplay(MLEntity* pEntity, char* fileName, cocos2d::CCLayer* parentLayer)
	:MLComponent(ML_COMTYPE_DISPLAY, pEntity)
	,m_Layer(parentLayer)
	,m_Sprite(NULL)
{
	ML_SAFE_ASSERT(fileName != NULL, "Please pass a valid file name");
	ML_SAFE_ASSERT(parentLayer != NULL, "Please pass a valid layer");
	m_Layer->retain();

	m_Sprite = CCSprite::create(fileName);
	ML_SAFE_ASSERT(m_Sprite != NULL, "Create sprite failed");
	m_Sprite->retain();

	m_Layer->addChild(m_Sprite, -10);
}

MLComDisplay::~MLComDisplay()
{
	if(m_Sprite)
	{
		m_Sprite->removeFromParent();
		m_Sprite->release();
		m_Sprite = NULL;
	}

	if(m_Layer)
	{
		m_Layer->release();
		m_Layer = NULL;
	}
}

CCSprite* MLComDisplay::GetSprite() const
{
	return m_Sprite;
}