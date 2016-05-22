#include "ml_com_transform.h"

using namespace magicland;

MLComTransform::MLComTransform(MLEntity* entity, float x, float y, float sx, float sy, float rx, float ry)
	:MLComponent(ML_COMTYPE_TRANSFORM, entity)
	,m_Pos(MAKE_VECTOR2(x,y))
	,m_Scale(MAKE_VECTOR2(sx,sy))
	,m_Rot(MAKE_VECTOR2(rx, ry)) {
}

MLComTransform::~MLComTransform() {
}

void MLComTransform::SetPos(float x, float y) {
	m_Pos.x = x;
	m_Pos.y = y;
}

VECTOR2 MLComTransform::GetPos() const {
	return m_Pos;
}

void MLComTransform::SetScale(float sx, float sy) {
	m_Scale.x = sx;
	m_Scale.y = sy;
}

VECTOR2 MLComTransform::GetScale() const {
	return m_Scale;
}

void MLComTransform::SetRot(float rx, float ry) {
	m_Rot.x = rx;
  m_Rot.y = ry;
}

VECTOR2 MLComTransform::GetRot() const {
	return m_Rot;
}

float MLComTransform::VecToDegree(VECTOR2 vec) {
  VECTOR2 normal;
  Vec2Normalize(normal, vec);
  
  float result = 0.0f;
  if(abs(vec.x) < EPSILON) {
    if(vec.y < 0.0f) {
      result = -90.0f;
    } else {
      result = 90.0f;
    }
  } else {
    result = 180.0f * atan2f(vec.y, vec.x)/3.14159f;
  }

  return result;
} 