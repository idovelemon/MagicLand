#include "ml_com_weapons.h"

namespace magicland {

MLComWeapons::MLComWeapons(MLEntity* entity)
:MLComponent(ML_COMTYPE_WEAPONS, entity)
,m_CurWeaponIndex(-1)
,m_CurWeaponType(weapon::kWeaponUnKnown){
  m_Weapons.clear();
}

MLComWeapons::~MLComWeapons() {
  RemoveAllWeapons();

  m_CurWeaponIndex = -1;
  m_CurWeaponType = weapon::kWeaponUnKnown;
}

void MLComWeapons::AddWeapon(weapon::MLWeapon* weapon) {
  ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
  if(weapon != NULL) {
    m_Weapons.push_back(weapon);
    ML_SAFE_GRAB(weapon);
  }
}

void MLComWeapons::RemoveWeapon(int32_t type) {
  ML_SAFE_ASSERT(weapon::kWeaponUnKnown < type && type < weapon::kWeaponTotal, "Weapon Type Error");
  
  if(weapon::kWeaponUnKnown < type && type < weapon::kWeaponTotal) {
    std::vector<weapon::MLWeapon*>::iterator it = m_Weapons.begin();
    
    for(; it != m_Weapons.end(); ++it) {
      weapon::MLWeapon* weapon = *it;
      ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
      
      if(weapon != NULL) {
        
        if(weapon->GetType() == type) {
          ML_SAFE_DROP(weapon);
          m_Weapons.erase(it);
          break;
        }
      }
    }
  }
}

void MLComWeapons::RemoveAllWeapons() {
  for(int32_t i = 0; i < m_Weapons.size(); i++) {
    weapon::MLWeapon* weapon = m_Weapons[i];
    ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
    ML_SAFE_DROP(weapon);
  }

  m_Weapons.clear();
}

void MLComWeapons::SetCurWeaponType(int32_t type) {
  ML_SAFE_ASSERT(weapon::kWeaponUnKnown < type && type < weapon::kWeaponTotal, "Weapon Type Error");
  if(weapon::kWeaponUnKnown < type && type < weapon::kWeaponTotal) {
    
    bool is_found = false;
    for(int32_t i = 0; i < m_Weapons.size(); i++) {
      weapon::MLWeapon* weapon = m_Weapons[i];
      ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");

      if(weapon != NULL) {
        if(weapon->GetType() == type) {
          m_CurWeaponIndex = i;
          is_found = true;
        }
      }
    }

    ML_SAFE_ASSERT(is_found == true, "No Weapon Error");
    
    if(is_found == true) {
      m_CurWeaponType = type;
    }
  }
}

int32_t MLComWeapons::GetCurWeaponType() {
  return m_CurWeaponType;
}

void MLComWeapons::StartWeapon() {
  ML_SAFE_ASSERT(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal, "Weapon Type Error");
  
  if(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal) {
    ML_SAFE_ASSERT(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size(), "Size Error");

    if(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size()) {
      weapon::MLWeapon* weapon = m_Weapons[m_CurWeaponIndex];

      ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
      if(weapon != NULL) {
        weapon->Start();
      }
    }
  }
}

void MLComWeapons::EndWeapon() {
  ML_SAFE_ASSERT(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal, "Weapon Type Error");
  
  if(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal) {
    ML_SAFE_ASSERT(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size(), "Size Error");

    if(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size()) {
      weapon::MLWeapon* weapon = m_Weapons[m_CurWeaponIndex];

      ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
      if(weapon != NULL) {
        weapon->End();
      }
    }
  }
}

void MLComWeapons::Run(float delta) {
  ML_SAFE_ASSERT(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal, "Weapon Type Error");
  
  if(weapon::kWeaponUnKnown < m_CurWeaponType && m_CurWeaponType < weapon::kWeaponTotal) {
    ML_SAFE_ASSERT(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size(), "Size Error");

    if(0 <= m_CurWeaponIndex && m_CurWeaponIndex < m_Weapons.size()) {
      weapon::MLWeapon* weapon = m_Weapons[m_CurWeaponIndex];

      ML_SAFE_ASSERT(weapon != NULL, "Null Pointer Error");
      if(weapon != NULL) {
        weapon->Run(delta);
      }
    }
  }
}

}; // namespace magicland