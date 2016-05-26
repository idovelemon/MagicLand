//----------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 24
// Brief: Control entity's behavior on one state
//----------------------------------------------------------
#ifndef ML_FSM_MLSTATE_H_
#define ML_FSM_MLSTATE_H_

#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

namespace fsm {

class MLState:public MLReference {
public:
  MLState(MLEntity* entity)
    :m_Entity(entity)
    ,m_IsOver(false) {
  }
  
  virtual ~MLState() {
  }

public:
  virtual void Enter(float delta) = 0;
  virtual void Run(float delta) = 0;
  virtual void Exit(float delta) = 0;

  virtual bool IsOver() const {
    return m_IsOver;
  }

protected:
  bool          m_IsOver;
  MLEntity*     m_Entity;
};

} // namespace magicland

} // namespace magicland

#endif // ML_FSM_MLSTATE_H_