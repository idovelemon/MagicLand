//-----------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon[1322600812@qq.com]
// Date: 2016 / 05 / 22
// Brief: A weapon will generate some sort of bullets
//-----------------------------------------------------------
#ifndef ML_ECS_MLWEAPON_H_
#define ML_ECS_MLWEAPON_H_

#include <stdint.h>

#include "reference/ml_reference.h"

namespace magicland {

class MLEntity;

namespace weapon {
//-------------------------------------------------------------------
// Local/Constant
//-------------------------------------------------------------------
const int32_t kWeaponUnKnown = -1;
const int32_t kWeaponSingleParticle = 0;
const int32_t kWeaponTotal = 1;

//-------------------------------------------------------------------
// Class/Typedef
//-------------------------------------------------------------------
class MLWeapon:public MLReference {
public:
  MLWeapon(int32_t type)
  :m_Type(type)
  ,m_IsStart(false)
  ,m_OwnnerEntity(NULL) {
  }

  virtual ~MLWeapon() {
  }

public:
  virtual int32_t GetType() { return m_Type;}
  virtual void SetOwnner(MLEntity* entity) { m_OwnnerEntity = entity;}
  virtual void Start() { m_IsStart = true;}
  virtual void End() { m_IsStart = false;}

  virtual void Run(float delta) = 0;

protected:
  int32_t         m_Type;
  bool            m_IsStart;
  MLEntity*       m_OwnnerEntity;

private:
  ML_DISALLOW_COPY_AND_ASSIGN(MLWeapon);
};

} // namespace weapon

} // namespace magicland
#endif // ML_ECS_MLWEAPON_H_