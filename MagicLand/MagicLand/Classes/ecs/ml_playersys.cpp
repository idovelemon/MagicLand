#include "ml_playersys.h"

#include "ml_allcoms.h"
#include "ml_entity.h"

#include <Windows.h>

namespace magicland {

MLPlayerSys::MLPlayerSys(MLEntity* entity)
:MLSystem(entity) {
}

MLPlayerSys::~MLPlayerSys() {
}

void MLPlayerSys::Run(float delta) {
  MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
  ML_SAFE_ASSERT(transform != NULL, "Null Pointer Error");

  MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
  ML_SAFE_ASSERT(display != NULL, "Null Pointer Error");

  if(transform != NULL && display != NULL) {
    VECTOR2 pos = transform->GetPos();
    if(GetKeyState('A') & 0x8000) {
      pos.x -= 5.0f;
    } else if(GetKeyState('D') & 0x8000) {
      pos.x += 5.0f;
    }

    if(GetKeyState('W') & 0x8000) {
      pos.y += 5.0f;
    } else if(GetKeyState('S') & 0x8000) {
      pos.y -= 5.0f;
    }

    transform->SetPos(pos.x, pos.y);
    display->GetSprite()->setPosition(ccp(pos.x, pos.y));
  }

  if(GetKeyState('J') & 0x8000) {
    MLComWeapons* weapons = reinterpret_cast<MLComWeapons*>(m_Entity->GetComponent(ML_COMTYPE_WEAPONS));
    ML_SAFE_ASSERT(weapons != NULL, "No Component Error");

    weapons->StartWeapon();
  }
}

} // namespace magicland