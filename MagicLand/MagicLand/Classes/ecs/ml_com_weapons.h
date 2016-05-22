//-----------------------------------------------------------------
// Declaration: Copyright (c), by i_dovelemon, 2016. All right reserved.
// Author: i_dovelemon
// Date: 2016 / 05 / 22
// Version: 1.0
// Brief: Contains one entity's all weapon
//-----------------------------------------------------------------
#ifndef ML_ECS_MLCOMWEAPON_H_
#define ML_ECS_MLCOMWEAPON_H_

#include <stdint.h>
#include <vector>

#include "ml_component.h"
#include "ml_weapon.h"

namespace magicland {

class weapon::MLWeapon;

class MLComWeapons:public MLComponent{
public:
  MLComWeapons(MLEntity* entity);
  virtual ~MLComWeapons();

public:
  void AddWeapon(weapon::MLWeapon* weapon);
  void RemoveWeapon(int32_t type);
  void RemoveAllWeapons();

  void SetCurWeaponType(int32_t type);
  int32_t GetCurWeaponType();

  void StartWeapon();
  void EndWeapon();

  void Run(float delta);

private:
  std::vector<weapon::MLWeapon*>      m_Weapons;
  int32_t                             m_CurWeaponIndex;
  int32_t                             m_CurWeaponType;
};

} // namespace magicland
#endif // ML_ECS_MLCOMWEAPON_H_