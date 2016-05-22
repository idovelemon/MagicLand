#include "ml_normalflysys.h"

#include "ml_allcoms.h"
#include "ml_entity.h"

namespace magicland {

MLNormalFlySys::MLNormalFlySys(MLEntity* entity)
:MLSystem(entity) {
}

MLNormalFlySys::~MLNormalFlySys() {
}

void MLNormalFlySys::Run(float delta) {
  ML_SAFE_ASSERT(m_Entity != NULL, "No Entity Error");
  if(m_Entity != NULL) {
    MLComTransform* transform = reinterpret_cast<MLComTransform*>(m_Entity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(transform != NULL, "No Component Error");
    
    MLComSpeed* speed = reinterpret_cast<MLComSpeed*>(m_Entity->GetComponent(ML_COMTYPE_SPEED));
    ML_SAFE_ASSERT(speed != NULL, "No Component Error");

    MLComDisplay* display = reinterpret_cast<MLComDisplay*>(m_Entity->GetComponent(ML_COMTYPE_DISPLAY));
    ML_SAFE_ASSERT(display != NULL, "No Component Error");

    MLComUserData* user_data = reinterpret_cast<MLComUserData*>(m_Entity->GetComponent(ML_COMTYPE_USERDATA));
    ML_SAFE_ASSERT(user_data != NULL, "No Component Error");

    if(transform != NULL
      && speed != NULL
      && display != NULL
      && user_data != NULL) {
        // Move
        VECTOR2 pos = transform->GetPos();
        VECTOR2 dir = transform->GetRot();
        float pos_speed = speed->GetPosSpeed();
        pos.x += dir.x * pos_speed;
        pos.y += dir.y * pos_speed;
        transform->SetPos(pos.x, pos.y);

        // Check if it is outof the Range of fire
        int32_t range = reinterpret_cast<int32_t>(user_data->GetValueByCategory(kUserDataTag_RangeOfFire));
        int32_t cur_range = reinterpret_cast<int32_t>(user_data->GetValueByCategory(kUserDataTag_CurRangeOfFire));
        if(cur_range >= range) {
          m_Entity->KillEntity();
        } else {
          cur_range += pos_speed;
          user_data->UpdateValue(kUserDataTag_CurRangeOfFire, reinterpret_cast<void*>(cur_range));
        }

        // Draw
        display->GetSprite()->setPosition(ccp(pos.x, pos.y));
    }
  }
}

} // namespace magicland