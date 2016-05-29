#include "ml_closeupstate.h"

#include "cocos2d.h"

#include "ecs/ml_allcoms.h"
#include "ecs/ml_entity.h"

namespace magicland {

namespace evilcircle {

const float kMaxScale = 2.0f;
const float kNormalScale = 1.0f;
const float kTipNameInitX = 800.0f;
const float kTipNameInitY = 30.0f;
const float kTipNameSlowX = 200.0f;
const float kTipNameEndX = 100;
const float kTipDifficultyInitX = 0.0f;
const float kTipDifficultyInitY = 600.0f - 30.0f;
const float kTipDifficultySlowX = 600.0f;
const float kTipDifficultyEndX = 700.0f;
const float kNormalFlyInSpeed = 30.0f;
const float kSlowRate = 0.02f;

MLCloseUpState::MLCloseUpState(MLEntity* entity)
:MLState(entity)
,m_CurState(ML_STATE_ZOOMIN)
,m_TipName(NULL)
,m_TipDifficulty(NULL) {
}

MLCloseUpState::~MLCloseUpState() {
  if(m_TipName != NULL) {
    m_TipName->removeFromParent();
    m_TipName->release();
    m_TipName = NULL;
  }

  if(m_TipDifficulty != NULL) {
    m_TipDifficulty->removeFromParent();
    m_TipDifficulty->release();
    m_TipDifficulty = NULL;
  }
}

void MLCloseUpState::Enter(float delta) {
  m_CurState = ML_STATE_ZOOMIN;

  // Create tip
  m_TipName = cocos2d::CCSprite::create("Image/EvilCircle/TipName.png");
  ML_SAFE_ASSERT(m_TipName != NULL, "Sprite Create Error");
  if(m_TipName != NULL) {
    m_TipName->retain();
  }

  m_TipDifficulty = cocos2d::CCSprite::create("Image/EvilCircle/Difficulty.png");
  ML_SAFE_ASSERT(m_TipDifficulty != NULL, "Sprite Create Error");
  if(m_TipDifficulty != NULL) {
    m_TipDifficulty->retain();
  }
}

void MLCloseUpState::Run(float delta) {
  cocos2d::CCLayer* layer = reinterpret_cast<cocos2d::CCLayer*>(cocos2d::CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1));
  ML_SAFE_ASSERT(layer != NULL, "No Layer Error");

  if(layer != NULL) {
    switch(m_CurState) {
    case ML_STATE_ZOOMIN:
      if(ZoomIn(layer, delta)) {
        m_CurState = ML_STATE_TIP;
      }
      break;

    case ML_STATE_TIP:
      if(Tip(layer, delta)) {
        m_CurState = ML_STATE_ZOOMOUT;
      }
      break;

    case ML_STATE_ZOOMOUT:
      if(ZoomOut(layer, delta)) {
        m_IsOver = true;
      }
      break;

    default:
      ML_SAFE_ASSERT(0, "State Error");
      break;
    }
  }
}

void MLCloseUpState::Exit(float delta) {
}

bool MLCloseUpState::ZoomIn(cocos2d::CCLayer* layer, float delta) {
  bool result = false;
  
  ML_SAFE_ASSERT(layer != NULL, "No Layer Error");
  if(layer != NULL && m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {

      // Zoom in
      VECTOR2 pos = transform->GetPos();
      VECTOR2 anchor_point = MAKE_VECTOR2(pos.x / 800, pos.y / 600);
      layer->setAnchorPoint(ccp(anchor_point.x, anchor_point.y));
      float scale = layer->getScale();
      scale += 0.1f;

      if(scale >= kMaxScale) {
        scale = kMaxScale;
        result = true;
      }

      layer->setScale(scale);

      // Still rotate
      VECTOR2 rot = transform->GetRot();
      float degree = transform->VecToDegree(transform->GetRot());
      degree += speed->GetRotSpeed();
      rot.x = cos(degree / 180.0f * 3.14159);
      rot.y = sin(degree / 180.0f * 3.14159);
      transform->SetRot(rot.x, rot.y);

      // Update display component
      display->GetSprite()->setRotation(degree);
    }
  }

  return result;
}

bool MLCloseUpState::Tip(cocos2d::CCLayer* layer, float delta) {
  bool result = false;
  enum {
    ML_TIPSTATE_ENTER,

    ML_TIPSTATE_FLYIN,
    ML_TIPSTATE_SLOWIN,

    ML_TIPSTATE_EXIT
  };
  static int32_t s_TipState = ML_TIPSTATE_ENTER;
  float fly_in_speed = 0;

  ML_SAFE_ASSERT(layer != NULL, "No Layer Error");
  if(layer != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {
      switch(s_TipState) {
      case ML_TIPSTATE_ENTER:
        layer->getParent()->addChild(m_TipName);
        layer->getParent()->addChild(m_TipDifficulty);
        m_TipName->setPosition(ccp(kTipNameInitX, kTipNameInitY));
        m_TipDifficulty->setPosition(ccp(kTipDifficultyInitX, kTipDifficultyInitY));
        s_TipState = ML_TIPSTATE_FLYIN;
        break;

      case ML_TIPSTATE_FLYIN:
        {
           // Fly in
          float fly_in_speed = kNormalFlyInSpeed;
          float tip_name_pos = m_TipName->getPositionX();
          float tip_difficulty_pos = m_TipDifficulty->getPositionX();
          tip_name_pos -= kNormalFlyInSpeed;
          tip_difficulty_pos += kNormalFlyInSpeed;
          m_TipName->setPositionX(tip_name_pos);
          m_TipDifficulty->setPositionX(tip_difficulty_pos);
          if(tip_name_pos < kTipNameSlowX && tip_difficulty_pos > kTipDifficultySlowX) {
            s_TipState = ML_TIPSTATE_SLOWIN;
          }

          // Rotate
          VECTOR2 rot = transform->GetRot();
          float degree = transform->VecToDegree(transform->GetRot());
          degree += speed->GetRotSpeed();
          rot.x = cos(degree / 180.0f * 3.14159);
          rot.y = sin(degree / 180.0f * 3.14159);
          transform->SetRot(rot.x, rot.y);

          // Update display component
          display->GetSprite()->setRotation(degree);
        }
        break;

      case ML_TIPSTATE_SLOWIN:
        {
          // Slow fly in
          float fly_in_speed = kNormalFlyInSpeed * kSlowRate;
          float tip_name_pos = m_TipName->getPositionX();
          float tip_difficulty_pos = m_TipDifficulty->getPositionX();
          tip_name_pos -= fly_in_speed;
          tip_difficulty_pos += fly_in_speed;
          m_TipName->setPositionX(tip_name_pos);
          m_TipDifficulty->setPositionX(tip_difficulty_pos);
          if(tip_name_pos < kTipNameEndX && tip_difficulty_pos > kTipDifficultyEndX) {
            s_TipState = ML_TIPSTATE_EXIT;
          }

          // Rotate
          VECTOR2 rot = transform->GetRot();
          float degree = transform->VecToDegree(transform->GetRot());
          degree += speed->GetRotSpeed() * kSlowRate;
          rot.x = cos(degree / 180.0f * 3.14159);
          rot.y = sin(degree / 180.0f * 3.14159);
          transform->SetRot(rot.x, rot.y);

          // Update display component
          display->GetSprite()->setRotation(degree);
        }
        break;

      case ML_TIPSTATE_EXIT:
        {
          layer->getParent()->removeChild(m_TipName);
          layer->getParent()->removeChild(m_TipDifficulty);
          m_TipName->setPosition(ccp(kTipNameInitX, kTipNameInitY));
          m_TipDifficulty->setPosition(ccp(kTipDifficultyInitX, kTipDifficultyInitY));
          s_TipState = ML_TIPSTATE_FLYIN;
          result = true;
        }
        break;
      }
    }
  }

  return result;
}

bool MLCloseUpState::ZoomOut(cocos2d::CCLayer* layer, float delta) {
  bool result = false;

  ML_SAFE_ASSERT(layer != NULL, "No Layer Error");
  if(layer != NULL && m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {

      // Zoom out
      VECTOR2 pos = transform->GetPos();
      VECTOR2 anchor_point = MAKE_VECTOR2(pos.x / 800, pos.y / 600);
      layer->setAnchorPoint(ccp(anchor_point.x, anchor_point.y));
      float scale = layer->getScale();
      scale -= 0.05f;

      if(scale <= kNormalScale) {
        scale = kNormalScale;
        result = true;
      }

      layer->setScale(scale);

      // Still rotate
      VECTOR2 rot = transform->GetRot();
      float degree = transform->VecToDegree(transform->GetRot());
      degree += speed->GetRotSpeed();
      rot.x = cos(degree / 180.0f * 3.14159);
      rot.y = sin(degree / 180.0f * 3.14159);
      transform->SetRot(rot.x, rot.y);

      // Update display component
      display->GetSprite()->setRotation(degree);
    }
  }

  return result;
}

} // namespace evilcircle

} // namespace magicland