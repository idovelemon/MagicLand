#include "ml_com_display.h"

#include "marco.h"
#include "ml_entity.h"

using namespace magicland;
using namespace cocos2d;

MLComDisplay::MLComDisplay(MLEntity* entity, char* fileName, cocos2d::CCLayer* parentLayer)
	:MLComponent(ML_COMTYPE_DISPLAY, entity)
	,m_Layer(parentLayer)
	,m_Sprite(NULL) {

	ML_SAFE_ASSERT(fileName != NULL, "Please pass a valid file name");
	ML_SAFE_ASSERT(parentLayer != NULL, "Please pass a valid layer");
	
  if (fileName != NULL && parentLayer != NULL) {
		m_Layer->retain();

		m_Sprite = CCSprite::create(fileName);
		ML_SAFE_ASSERT(m_Sprite != NULL, "Create sprite failed");
		
    if (m_Sprite != NULL) {
			m_Sprite->retain();

			m_Layer->addChild(m_Sprite, -10);
		}
	}
}

MLComDisplay::~MLComDisplay() {
	if(m_Sprite) {
		m_Sprite->removeFromParent();
		m_Sprite->release();
		m_Sprite = NULL;
	}

	if(m_Layer) {
		m_Layer->release();
		m_Layer = NULL;
	}
}

CCSprite* MLComDisplay::GetSprite() const {
	return m_Sprite;
}