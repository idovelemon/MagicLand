#include "ml_movetocenterstate.h"

#include "ecs/ml_allcoms.h"
#include "ecs/ml_entity.h"

namespace magicland {

namespace evilcircle {

MLMoveToCenterState::MLMoveToCenterState(MLEntity* entity)
:MLState(entity) {
}

MLMoveToCenterState::~MLMoveToCenterState() {
}

void MLMoveToCenterState::Enter(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    if(speed != NULL) {
      
      // Speed up the rotation
      float rot_speed = speed->GetRotSpeed();
      rot_speed += 10.0f;
      speed->SetRotSpeed(rot_speed);

      // Set the move speed
      speed->SetPosSpeed(5.0f);
    }
  }
}

void MLMoveToCenterState::Run(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");

    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    if(transform != NULL && speed != NULL && display != NULL) {

      // Move to center
      VECTOR2 pos = transform->GetPos();
      VECTOR2 target_pos = MAKE_VECTOR2(400, 300);
      VECTOR2 to_target;
      Vec2Sub(to_target, target_pos, pos);
      float len = 0.0f;
      Vec2Length(len, to_target);
      VECTOR2 to_target_normal;
      Vec2Normalize(to_target_normal, to_target);
      pos.x += to_target_normal.x * speed->GetPosSpeed();
      pos.y += to_target_normal.y * speed->GetPosSpeed();
      
      if(speed->GetPosSpeed() >= len) {
        m_IsOver = true;
        pos.x = 400;
        pos.y = 300;
      }

      transform->SetPos(pos.x, pos.y);

      // Rotate
      VECTOR2 rot = transform->GetRot();
      float degree = transform->VecToDegree(transform->GetRot());
      degree += speed->GetRotSpeed();
      rot.x = cos(degree / 180.0f * 3.14159);
      rot.y = sin(degree / 180.0f * 3.14159);
      transform->SetRot(rot.x, rot.y);

      // Update display component
      display->GetSprite()->setPosition(ccp(transform->GetPos().x, transform->GetPos().y));
      display->GetSprite()->setRotation(degree);
    }
  }
}

void MLMoveToCenterState::Exit(float delta) {
  m_IsOver = false;

  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    if(speed != NULL) {
      float rot_speed = speed->GetRotSpeed();
      rot_speed -= 10.0f;
      speed->SetRotSpeed(rot_speed);
    }
  }
}

} // namespace evilcircle

} // namespace magicland