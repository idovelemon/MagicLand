#include "ml_evilcirclesys.h"

#include "ml_allcoms.h"
#include "ml_entity.h"
#include "fsm/ml_endstate.h"
#include "fsm/ml_statemachine.h"
#include "fsm/ml_startstate.h"
#include "fsm/evilcircle/ml_closeupstate.h"
#include "fsm/evilcircle/ml_inscenestate.h"
#include "fsm/evilcircle/ml_movetocenterstate.h"

namespace magicland {

MLEvilCircleSys::MLEvilCircleSys(MLEntity* entity)
:MLSystem(entity)
,m_StateMachine(NULL) {
  m_StateMachine = new fsm::MLStateMachine(entity);
  ML_SAFE_ASSERT(m_StateMachine != NULL, "Memory Error");

  if(m_StateMachine != NULL) {
    fsm::MLStartState* start_state = new fsm::MLStartState();
    ML_SAFE_ASSERT(start_state != NULL, "Memory Error");

    fsm::MLEndState* end_state = new fsm::MLEndState();
    ML_SAFE_ASSERT(end_state != NULL, "Memory Error");

    if(start_state != NULL && end_state != NULL) {
      evilcircle::MLInSceneState* in_scene_state = new evilcircle::MLInSceneState(entity);
      ML_SAFE_ASSERT(in_scene_state != NULL, "Memory Error");

      evilcircle::MLMoveToCenterState* move_to_center_state = new evilcircle::MLMoveToCenterState(entity);
      ML_SAFE_ASSERT(move_to_center_state != NULL, "Memory Error");

      evilcircle::MLCloseUpState* close_up_state = new evilcircle::MLCloseUpState(entity);
      ML_SAFE_ASSERT(close_up_state != NULL, "Memory Error");

      if(in_scene_state != NULL && move_to_center_state != NULL
        && close_up_state != NULL) {
        m_StateMachine->AddStateEntry(start_state, in_scene_state);
        m_StateMachine->AddStateEntry(in_scene_state, move_to_center_state);
        m_StateMachine->AddStateEntry(move_to_center_state, close_up_state);
        m_StateMachine->AddStateEntry(close_up_state, end_state);

        m_StateMachine->SetCurState(start_state);

        ML_SAFE_DROP(in_scene_state);
        ML_SAFE_DROP(move_to_center_state);
        ML_SAFE_DROP(close_up_state);
      }

      ML_SAFE_DROP(start_state);
      ML_SAFE_DROP(end_state);
    }
  }
}

MLEvilCircleSys::~MLEvilCircleSys() {
  ML_SAFE_DROP(m_StateMachine);
}

void MLEvilCircleSys::Run(float delta) {
  ML_SAFE_ASSERT(m_StateMachine != NULL, "No StateMachine Error");
  if(m_StateMachine != NULL) {
    m_StateMachine->Run(delta);
  }
}

} // namespace magicland