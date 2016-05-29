//-------------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 26
// Brief: The evil circle will zoom in the scene
//-------------------------------------------------------------------------
#ifndef ML_FSM_EVILCIRCLE_MLINSCENESTATE_H_
#define ML_FSM_EVILCIRCLE_MLINSCENESTATE_H_

#include "fsm/ml_state.h"

namespace magicland {

namespace evilcircle {

class MLInSceneState:public fsm::MLState {
public:
  MLInSceneState(MLEntity* entity);
  virtual ~MLInSceneState();

public:
  virtual void Enter(float delta);
  virtual void Run(float delta);
  virtual void Exit(float delta);

protected:
  float     m_CurVortexAngle;
};

} // namespace evilcircle

} // namespace magicland

#endif // ML_FSM_EVILCIRCLE_MLINSCENESTATE_H_