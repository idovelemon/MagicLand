#include "ml_single_particle.h"

#include "ml_allcoms.h"
#include "ml_entity.h"
#include "ml_normalflysys.h"
#include "round/ml_entitymgr.h"

namespace magicland {

namespace weapon {

MLSingleParticle::MLSingleParticle()
:MLWeapon(kWeaponSingleParticle)
,m_Delta(-1) {
}

MLSingleParticle::~MLSingleParticle() {
}

void MLSingleParticle::Run(float delta) {
  if(m_IsStart) {
    if(m_Delta == -1) {
      ML_SAFE_ASSERT(m_OwnnerEntity != NULL, "No Ownner Error");
    
      if(m_OwnnerEntity != NULL) {
        MLEntity* entity = CreateSingleParticle();
        ML_SAFE_ASSERT(entity != NULL, "Null Pointer Error");
        if(entity != NULL) {
          MLEntityMgr::AddEntity(entity);
          ML_SAFE_DROP(entity);
          m_Delta = 10;
        }
      }
    } else {
      m_Delta--;
      if(m_Delta == 0) {
        m_IsStart = false;
        m_Delta = -1;
      }
    }
  }
}

MLEntity* MLSingleParticle::CreateSingleParticle() {
  MLEntity* entity = NULL;

  ML_SAFE_ASSERT(m_OwnnerEntity != NULL, "No Ownner Error");
  
  if(m_OwnnerEntity != NULL) {
    MLComTransform* ownner_transform = reinterpret_cast<MLComTransform*>(m_OwnnerEntity->GetComponent(ML_COMTYPE_TRANSFORM));
    ML_SAFE_ASSERT(ownner_transform != NULL, "No Component Error");

    if(ownner_transform != NULL) {
      entity = new MLEntity(ML_ETYMAINTYPE_PLAYERATTACK, ML_ETYSUBTYPE_SINGLEPARTICLE);
      ML_SAFE_ASSERT(entity != NULL, "Memory Error");

      if(entity != NULL) {
        // Create transform
        MLComTransform* transform = new MLComTransform(entity
          ,ownner_transform->GetPos().x, ownner_transform->GetPos().y
          ,1.0f, 1.0f
          ,0.0f, 1.0f);
        ML_SAFE_ASSERT(transform != NULL, "Memory Error");
        if(transform != NULL) {
          entity->AddComponent(transform);
          ML_SAFE_DROP(transform);
        }

        // Create speed
        MLComSpeed* speed = new MLComSpeed(entity, 10.0f, 0.0f, 0.0f);
        ML_SAFE_ASSERT(speed != NULL, "Memory Error");
        if(speed != NULL) {
          entity->AddComponent(speed);
          ML_SAFE_DROP(speed);
        }
       
        // Create display
        MLComDisplay* display = new MLComDisplay(entity, "Image/Weapon/Particle.png"
          ,reinterpret_cast<cocos2d::CCLayer*>(cocos2d::CCDirector::sharedDirector()->getRunningScene()->getChildByTag(1)));
        ML_SAFE_ASSERT(display != NULL, "Memory Error");
        if(display != NULL) {
           entity->AddComponent(display);
           display->GetSprite()->setAnchorPoint(ccp(0.5f, 0.5f));
           display->GetSprite()->setPosition(ccp(ownner_transform->GetPos().x, ownner_transform->GetPos().y));
           ML_SAFE_DROP(display);
        }

        // Create user data
        MLComUserData* user_data = new MLComUserData(entity);
        ML_SAFE_ASSERT(user_data != NULL, "Memory Error");
        if(user_data != NULL) {
          entity->AddComponent(user_data);
          int32_t range = 800; // TODO: int32_t is not accurate
          user_data->PushValue(kUserDataTag_RangeOfFire, MLComUserData::USER_DATA_TYPE_INTEGER, reinterpret_cast<void*>(range));

          int32_t cur_range = 0;
          user_data->PushValue(kUserDataTag_CurRangeOfFire, MLComUserData::USER_DATA_TYPE_INTEGER, reinterpret_cast<void*>(cur_range));
          ML_SAFE_DROP(user_data);
        }

        // Create system
        MLSystem* system = new MLNormalFlySys(entity);
        ML_SAFE_ASSERT(system != NULL, "Memory Error");
        if(system != NULL) {
          entity->AttachSystem(system);
        }
        ML_SAFE_DROP(system);
      }
    }
  }

  return entity;
}

} // namespace weapon

} // namespace magicland