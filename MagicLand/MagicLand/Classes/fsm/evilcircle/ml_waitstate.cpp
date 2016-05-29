#include "ml_waitstate.h"

#include "ecs/ml_allcoms.h"
#include "ecs/ml_entity.h"

namespace magicland {

namespace evilcircle {

const float kWaitTime = 30.0f;

MLWaitState::MLWaitState(MLEntity* entity)
:MLState(entity)
,m_WaitTime(0.0f) {
}

MLWaitState::~MLWaitState() {
}

void MLWaitState::Enter(float delta) {
}

void MLWaitState::Run(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {

      // Wait
      m_WaitTime += 1.0f;
      if(m_WaitTime > kWaitTime) {
        m_IsOver = true;
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
  }
}

void MLWaitState::Exit(float delta) {
  m_IsOver = false;
  m_WaitTime = 0.0f;
}

} // namespace evilcircle

} // namespace magicland