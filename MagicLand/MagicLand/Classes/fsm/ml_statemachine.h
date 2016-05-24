//--------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 24
// Brief: State machine will control the state transformation of entity
//--------------------------------------------------------------
#ifndef ML_FSM_MLSTATEMACHINE_H_
#define ML_FSM_MLSTATEMACHINE_H_

#include <vector>

#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

namespace fsm {

//------------------------------------------------------------------------
// Declaration
//------------------------------------------------------------------------
class MLState;
typedef bool (*MLCondition)(MLEntity*);

//------------------------------------------------------------------------
// Class
//------------------------------------------------------------------------
class MLStateMachine: public MLReference{
public:
  MLStateMachine(MLEntity* entity);
  virtual ~MLStateMachine();

public:
  //-----------------------------------------------------------------------
  // Desc: Add the state entry into the state machine
  // Param: start The start state of the entry
  // Param: con If the condition matched, the state will become the end
  // Param: end The end state of the entry
  //-----------------------------------------------------------------------
  void AddStateEntry(MLState* start, MLCondition con, MLState* end);

  //-----------------------------------------------------------------------
  // Desc: Run the state machine
  //-----------------------------------------------------------------------
  void Run(float delta);

  void SetCurState(MLState* state);

protected:
  struct MLStateEntry {
    MLState* start;
    MLCondition con;
    MLState* end;
  };

  std::vector<MLState*>       m_States;
  std::vector<MLStateEntry>   m_StateEntries;
  MLState*                    m_CurState;
  MLEntity*                   m_Entity;
};

} // namespace fsm

} // namespace magicland

#endif // ML_FSM_MLSTATEMACHINE_H_