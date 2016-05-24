//----------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 24
// Brief: Every state in the state machine must set this state as the last one state
//----------------------------------------------------------------------
#ifndef ML_FSM_MLENDSTATE_H_
#define ML_FSM_MLENDSTATE_H_

#include "ml_state.h"

namespace magicland {

namespace fsm {

class MLEndState:public MLState {
public:
  MLEndState()
    :MLState(NULL) {
  }

  virtual ~MLEndState() {
  }

public:
  virtual void Enter(float delta) {
  }

  virtual void Run(float delta) {
  }

  virtual void Exit(float delta) {
  }
};

} // namespace fsm

} // namespace magicland

#endif