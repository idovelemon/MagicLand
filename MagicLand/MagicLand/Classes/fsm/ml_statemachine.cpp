#include "ml_statemachine.h"

#include <stdint.h>

#include "ml_state.h"

namespace magicland {

namespace fsm {

MLStateMachine::MLStateMachine(MLEntity* entity)
:m_CurState(NULL)
,m_Entity(entity) {
}

MLStateMachine::~MLStateMachine() {
  for(size_t i = 0; i < m_States.size(); i++) {
    MLState* state = m_States[i];
    ML_SAFE_ASSERT(state != NULL, "Null Pointer Error");
    ML_SAFE_DROP(state);
  }

  m_States.clear();
  m_StateEntries.clear();
  m_CurState = NULL;
}

void MLStateMachine::AddStateEntry(MLState* start, MLState* end) {
  ML_SAFE_ASSERT(start != NULL, "Invalid Parameter Error");
  ML_SAFE_ASSERT(end != NULL, "Invalid Parameter Error");

  if(start != NULL && end != NULL) {
    MLStateEntry entry;
    memset(&entry, 0, sizeof(entry));
    entry.start = start;
    entry.end = end;

    m_StateEntries.push_back(entry);

    bool is_found_start = false, is_found_end = false;
    for(size_t i = 0; i < m_States.size(); i++) {
      if(start == m_States[i]) {
        is_found_start = true;
      }

      if(end == m_States[i]) {
        is_found_end = true;
      }

      if(is_found_start && is_found_end) {
        break;
      }
    }

    if(is_found_start == false) {
      m_States.push_back(start);
      ML_SAFE_GRAB(start);
    }

    if(is_found_end == false) {
      m_States.push_back(end);
      ML_SAFE_GRAB(end);
    }
  }
}

void MLStateMachine::Run(float delta) {
  ML_SAFE_ASSERT(m_CurState != NULL, "Null Pointer Error");
  if(m_CurState != NULL) {
    m_CurState->Run(delta);

    for(size_t i = 0; i < m_StateEntries.size(); i++) {
      MLStateEntry entry = m_StateEntries[i];
      if(entry.start != NULL && entry.end != NULL) {
        if(entry.start == m_CurState) {
          if(entry.start->IsOver()) {
            entry.start->Exit(delta);
            m_CurState = entry.end;
            entry.end->Enter(delta);
          }
        }
      }
    }
  }
}

void MLStateMachine::SetCurState(MLState* state) {
  ML_SAFE_ASSERT(state != NULL, "Invalid Parameter Error");
  if(state != NULL) {
    m_CurState = state;
  }
}

} // namespace fsm

} // namespace magicland