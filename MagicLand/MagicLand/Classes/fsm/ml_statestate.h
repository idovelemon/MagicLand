//-----------------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 24
// Brief: Every state machine must set this as the first state
//-----------------------------------------------------------------------
#ifndef ML_FSM_MLSTARTSTATE_H_
#define ML_FSM_MLSTARTSTATE_H_

#include "ml_state.h"

namespace magicland {

namespace fsm {

class MLStartState:public MLState {
public:
  MLStartState()
  :MLState(NULL) {
  }

  virtual ~MLStartState() {
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