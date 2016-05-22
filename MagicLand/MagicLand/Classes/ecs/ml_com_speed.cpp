#include "ml_com_speed.h"

#include "ml_entity.h"

namespace magicland {

MLComSpeed::MLComSpeed(MLEntity* entity, float pos_speed, float scale_speed, float rot_speed)
:MLComponent(ML_COMTYPE_SPEED, entity)
,m_PosSpeed(pos_speed)
,m_ScaleSpeed(scale_speed)
,m_RotSpeed(rot_speed) {
}

MLComSpeed::~MLComSpeed() {
}

void MLComSpeed::SetPosSpeed(float pos_speed) {
  m_PosSpeed = pos_speed;
}

float MLComSpeed::GetPosSpeed() const {
  return m_PosSpeed;
}

void MLComSpeed::SetScaleSpeed(float scale_speed) {
  m_ScaleSpeed = scale_speed;
}

float MLComSpeed::GetScaleSpeed() const {
  return m_ScaleSpeed;
}

void MLComSpeed::SetRotSpeed(float rot_speed) {
  m_RotSpeed = rot_speed;
}

float MLComSpeed::GetRotSpeed() const {
  return m_RotSpeed;
}

} // namespace magicland