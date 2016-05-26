//------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 26
// Brief: Move to the center of the screen
//------------------------------------------------------------
#ifndef ML_FSM_EVILCIRCLE_MLMOVETOCENTERSTATE_H_
#define ML_FSM_EVILCIRCLE_MLMOVETOCENTERSTATE_H_

#include "fsm/ml_state.h"

namespace magicland {

namespace evilcircle {

class MLMoveToCenterState:public fsm::MLState {
public:
  MLMoveToCenterState(MLEntity* entity);
  virtual ~MLMoveToCenterState();

public:
  virtual void Enter(float delta);
  virtual void Run(float delta);
  virtual void Exit(float delta);
};

} // namespace evilcircle

} // namespace magicland

#endif // ML_FSM_EVILCIRCLE_MLMOVETOCENTERSTATE_H_