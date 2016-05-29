//-------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 29
// Brief: Give the evilcircle a extreme close-up
//-------------------------------------------------------------
#ifndef ML_FSM_EVILCIRCLE_MLCLOSEUPSTATE_H_
#define ML_FSM_EVILCIRCLE_MLCLOSEUPSTATE_H_

#include <stdint.h>

#include "marco.h"
#include "fsm/ml_state.h"

namespace cocos2d {

class CCLayer;
class CCSprite;

}

namespace magicland {

namespace evilcircle {

class MLCloseUpState:public fsm::MLState {
public:
  MLCloseUpState(MLEntity* entity);
  virtual ~MLCloseUpState();

public:
  virtual void Enter(float delta);
  virtual void Run(float delta);
  virtual void Exit(float delta);

protected:
  bool ZoomIn(cocos2d::CCLayer* layer, float delta);
  bool Tip(cocos2d::CCLayer* layer, float delta);
  bool ZoomOut(cocos2d::CCLayer* layer, float delta);

private:
  enum {
    ML_STATE_ZOOMIN,
    ML_STATE_TIP,
    ML_STATE_ZOOMOUT,
  };

  int32_t               m_CurState;
  cocos2d::CCSprite*    m_TipName;
  cocos2d::CCSprite*    m_TipDifficulty;

  ML_DISALLOW_COPY_AND_ASSIGN(MLCloseUpState);
};

} // namespace evilcircle

} // namespace magicland

#endif