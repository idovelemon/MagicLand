#include "ml_inscenestate.h"

#include "ecs/ml_allcoms.h"
#include "ecs/ml_entity.h"

namespace magicland {

namespace evilcircle {

MLInSceneState::MLInSceneState(MLEntity* entity)
  :MLState(entity) {
}

MLInSceneState::~MLInSceneState() {
}

void MLInSceneState::Enter(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {
      
      // Change the position of the evilcircle, set it at the right-up corner of the scene
      transform->SetPos(700, 450);

      // Set the scale to 0
      transform->SetScale(0.0f, 0.0f);

      // Set the scale speed
      speed->SetScaleSpeed(0.01f);

      // Set the rotation speed
      speed->SetRotSpeed(10.0f);

      // Update display component
      display->GetSprite()->setPosition(ccp(transform->GetPos().x, transform->GetPos().y));
      display->GetSprite()->setScale(0.0f);
    }
  }
}

void MLInSceneState::Run(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {

      // Zoom in
      float scale_speed = speed->GetScaleSpeed();
      VECTOR2 scale = transform->GetScale();
      scale.x += scale_speed;
      scale.y += scale_speed;
      if(scale.x > 1.0f || scale.y > 1.0f) {
        scale.x = 1.0f;
        scale.y = 1.0f;
        m_IsOver = true;
      }

      transform->SetScale(scale.x, scale.y);

      // Rotate
      VECTOR2 rot = transform->GetRot();
      float degree = transform->VecToDegree(transform->GetRot());
      degree += speed->GetRotSpeed();
      rot.x = cos(degree / 180.0f * 3.14159);
      rot.y = sin(degree / 180.0f * 3.14159);
      transform->SetRot(rot.x, rot.y);

      // Update display component
      display->GetSprite()->setPosition(ccp(transform->GetPos().x, transform->GetPos().y));
      display->GetSprite()->setScaleX(transform->GetScale().x);
      display->GetSprite()->setScaleY(transform->GetScale().y);
      display->GetSprite()->setRotation(degree);
    }
  }
}

void MLInSceneState::Exit(float delta) {
  m_IsOver = false;
}

} // namespace evilcircle

} // namespace magicland